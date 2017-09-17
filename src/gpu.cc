#include "gpu.hh"
#include <iostream>

#define READ(addr) m_mmu->read_byte(addr)
#define WRITE(addr, val) m_mmu->write_byte(addr, val)

GPU::GPU(){}

GPU::GPU(MMU *mmu, Screen *screen, Timer *timer){
	Init(mmu, screen, timer);
}

void GPU::Init(MMU *mmu, Screen *screen, Timer *timer){
	m_mmu = mmu;
	m_screen = screen;
	m_timer = timer;
	reset();
}

void GPU::reset(){
	m_gpu_cycles = m_timer->get();
	set_gpumode(GPUMODE_HBLANK, false);
}

void GPU::set_gpumode(uint8_t mode, bool set_interrupt){
	uint8_t lcdc_status = (READ(ADDR_LCDC_STATUS) & 0b11111100) | mode;

	if(set_interrupt){
		uint8_t intr = 0;
		switch(mode){
			case GPUMODE_HBLANK:
				intr = STAT_INTR_HBLANK; break;
			case GPUMODE_VBLANK:
				intr = STAT_INTR_VBLANK; break;
			case GPUMODE_OAM:
				intr = STAT_INTR_OAM; break;
		}

		if((lcdc_status & intr) == intr){
			m_mmu->write_bit(ADDR_INTERRUPT_FLAG, INTR_LCDC, 1);
		}
	}
	
	WRITE(ADDR_LCDC_STATUS, lcdc_status);
}

void GPU::cycle(){
	if(!m_mmu->read_bit(ADDR_LCD_CONTROL, LCDC_ENABLE_LCD)){
		m_gpu_cycles = m_timer->get();
		WRITE(ADDR_LCDC_Y_COORD, 0);
		set_gpumode(GPUMODE_VBLANK, false);
		return;
	}

	switch(READ(ADDR_LCDC_STATUS) & 0b11){
		case GPUMODE_HBLANK:
			if(m_timer->elapse(m_gpu_cycles, CYCLES_HBLANK)){
				m_mmu->increment(ADDR_LCDC_Y_COORD);
				if(READ(ADDR_LCDC_Y_COORD) == 144){
					m_screen->render(screenbuffer);
					set_gpumode(GPUMODE_VBLANK, true);
					m_mmu->write_bit(ADDR_INTERRUPT_FLAG, INTR_VBLANK, 1);
				}else{
					set_gpumode(GPUMODE_OAM, false);
				}
			}
			break;
		case GPUMODE_VBLANK:
			if(m_timer->elapse(m_gpu_cycles, CYCLES_VBLANK)){
				m_mmu->increment(ADDR_LCDC_Y_COORD);
				if(READ(ADDR_LCDC_Y_COORD) >= 154){
					WRITE(ADDR_LCDC_Y_COORD, 0);
					set_gpumode(GPUMODE_OAM, true);
				}
			}
			break;
		case GPUMODE_OAM:
			if(m_timer->elapse(m_gpu_cycles, CYCLES_OAM)){
				set_gpumode(GPUMODE_VRAM, false);
			}
			break;
		case GPUMODE_VRAM:
			if(m_timer->elapse(m_gpu_cycles, CYCLES_VRAM)){
				render_scanline();
				set_gpumode(GPUMODE_HBLANK, true);
			}
			break;
	}

	if(READ(ADDR_LCDC_Y_COORD) == READ(ADDR_LY_COMPARE)){
		m_mmu->write_bit(ADDR_LCDC_STATUS, STAT_LY_COINCIDENCE, 1);
		if(READ(ADDR_LCDC_STATUS) & STAT_INTR_LY_COINCIDENCE){
			m_mmu->write_bit(ADDR_INTERRUPT_FLAG, INTR_LCDC, 1);
		}
	}else{
		m_mmu->write_bit(ADDR_LCDC_STATUS, STAT_LY_COINCIDENCE, 0);
	}
}

void GPU::render_scanline(){
	if(m_mmu->read_bit(ADDR_LCD_CONTROL, LCDC_ENABLE_BG_WINDOW))
		render_scanline_tiles();
	if(m_mmu->read_bit(ADDR_LCD_CONTROL, LCDC_ENABLE_SPRITE))
		render_scanline_sprites();
}

void GPU::render_scanline_tiles(){
	uint8_t lcdc_y = m_mmu->read_byte(ADDR_LCDC_Y_COORD);
	uint8_t scroll_y = m_mmu->read_byte(ADDR_SCROLL_Y);
	uint8_t scroll_x = m_mmu->read_byte(ADDR_SCROLL_X);
	uint8_t window_y = m_mmu->read_byte(ADDR_WINDOW_Y_POS);
	uint8_t window_x = m_mmu->read_byte(ADDR_WINDOW_X_POS);
	
	bool render_window = m_mmu->read_bit(ADDR_LCD_CONTROL, LCDC_ENABLE_WINDOW) && (window_y <= lcdc_y);
	
	uint16_t addr_tiledata_region = m_mmu->read_bit(ADDR_LCD_CONTROL, LCDC_TILEDATA_BG_WINDOW)?0x8000:0x8800;
	uint16_t addr_tilemap_region;
	
	if(render_window)
		addr_tilemap_region = m_mmu->read_bit(ADDR_LCD_CONTROL, LCDC_TILEMAP_WINDOW)?0x9C00:0x9800;
	else
		addr_tilemap_region = m_mmu->read_bit(ADDR_LCD_CONTROL, LCDC_TILEMAP_BG)?0x9C00:0x9800;
	
	uint8_t tile_y = render_window?(lcdc_y - window_y):(scroll_y + lcdc_y);
	uint8_t tile_row = tile_y >> 3;

	for(uint8_t p = 0; p < 160; p++){
		uint8_t tile_x = (render_window && (p >= window_x))?(p - window_x):(p + scroll_x);
		uint8_t tile_col = tile_x >> 3;

		uint8_t tile_id = READ(addr_tilemap_region + (tile_row << 5) + tile_col);
		
		uint16_t addr_tiledata = get_addr_tiledata(addr_tiledata_region, tile_id, 16); //16 bytes per tile

		uint8_t line = (tile_y & 0b111) << 1;

		uint8_t data1 = READ(addr_tiledata + line);
		uint8_t data2 = READ(addr_tiledata + line + 1);

		uint8_t bit_color = 0b111 - (tile_x & 0b111);
		uint8_t color_id = (((data2 >> bit_color) & 1) << 1) | ((data1 >> bit_color) & 1);

		uint8_t *color = get_color_dmg(color_id, READ(ADDR_BG_WINDOW_PALETTE_DATA));
		
		screenbuffer[lcdc_y][p][0] = color[0];
		screenbuffer[lcdc_y][p][1] = color[1];
		screenbuffer[lcdc_y][p][2] = color[2];
	}
}
void GPU::render_scanline_sprites(){
	uint8_t sprite_height = m_mmu->read_bit(ADDR_LCD_CONTROL, LCDC_SIZE_SPRITE)?16:8;
	uint8_t lcdc_y = m_mmu->read_byte(ADDR_LCDC_Y_COORD);

	for(uint8_t sprite = 0; sprite < 40; sprite++){
		uint8_t sprite_index = sprite << 2;
		
		uint8_t sprite_y = m_mmu->read_byte(0xFE00 + sprite_index) - 16;
		uint8_t sprite_x = m_mmu->read_byte(0xFE00 + sprite_index + 1) - 8;
		uint8_t sprite_tile = m_mmu->read_byte(0xFE00 + sprite_index + 2);
		uint8_t sprite_flags =  m_mmu->read_byte(0xFE00 + sprite_index + 3);

		if((lcdc_y >= sprite_y) && (lcdc_y < (sprite_y + sprite_height))){
			uint8_t line = (sprite_flags & SPRITE_FLIP_Y)?((sprite_height - 1) - (lcdc_y - sprite_y)):(lcdc_y - sprite_y);
			uint16_t addr_tiledata = (0x8000 + (sprite_tile << 4) + (line << 1));
			
			uint8_t data1 = m_mmu->read_byte(addr_tiledata);
			uint8_t data2 = m_mmu->read_byte(addr_tiledata + 1);

			for(uint8_t b = 0; b < 8; b++){
				uint8_t bit_color = (sprite_flags & SPRITE_FLIP_Y)?(0b111 - b):b;
				uint8_t color_id = (((data2 >> bit_color) & 1) << 1) | ((data1 >> bit_color) & 1);

				uint8_t palette = READ(((sprite_flags >> 4) & 1)?ADDR_OBJECT_PALETTE_1_DATA:ADDR_OBJECT_PALETTE_0_DATA);
				uint8_t *color = get_color_dmg(color_id, palette);

				if(color[0] == 0xFF && color[1] == 0xFF && color[2] == 0xFF)
					continue;

				uint8_t pixel = sprite_x + (0b111 - b);
				
				screenbuffer[lcdc_y][pixel][0] = color[0];
				screenbuffer[lcdc_y][pixel][1] = color[1];
				screenbuffer[lcdc_y][pixel][2] = color[2];
			}
		}
	}
}

uint16_t GPU::get_addr_tiledata(uint16_t addr, uint8_t id, uint8_t size){
	if(addr == 0x8000) return addr + (id * size);
	return addr + ((((int8_t)id)+128) * size);
}

uint8_t* GPU::get_color_dmg(uint8_t id, uint8_t palette){
	static uint8_t color[3];
	
	//(id << 1) [+ 1] ... high [low] bits (mapping to dmg_white (0) to dmg_black(3))
	uint8_t c = (((palette >> ((id << 1) + 1)) & 1) << 1) | ((palette >> (id << 1)) & 1);

	for(uint8_t i = 0; i < 3; i++)
		color[i] = COLORS_DMG[c][i];
	
	return color;
}
GPU::~GPU(){}

#include "gpu.hh"
#include <iostream>

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
	lcd_control = 0x91;
	scroll_y = 0;
	scroll_x = 0;
	line_y = 0;
	palette_bg_window = 0xFC;
	palette_obj_0 = 0xFF;
	palette_obj_1 = 0xFF;
	window_y = 0;
	window_x = 0;

	lcdc_status = GPUMODE_HBLANK;//not in doc
}

void GPU::set_gpumode(uint8_t mode){
	lcdc_status = (lcdc_status & 0b11111100) | mode;
}

uint8_t GPU::read_byte(uint16_t addr){
	if(addr < 0xA000){
		return ram_video[addr & 0x1FFF];
	}else if(addr < 0xFEA0){
		return oam[addr & 0xFF];
	}

	switch(addr){
		case 0xFF40:
			return lcd_control;
		case 0xFF42:
			return scroll_y;
		case 0xFF43:
			return scroll_x;
		case 0xFF44:
			return line_y;
		case 0xFF41:
			return lcdc_status;
		case 0xFF47:
			return palette_bg_window;
		case 0xFF48:
			return palette_obj_0;
		case 0xFF49:
			return palette_obj_1;
		case 0xFF4A:
			return window_y;
		case 0xFF4B:
			return window_x;
	}
	
	return 0;
}

void GPU::write_byte(uint16_t addr, uint8_t val){
	if(addr < 0xA000){
		ram_video[addr & 0x1FFF] = val;
	}else if(addr < 0xFEA0){
		oam[addr & 0xFF] = val;
	}

	switch(addr){
		case 0xFF40:
			lcd_control = val; break;
		case 0xFF42:
			scroll_y = val; break;
		case 0xFF43:
			scroll_x = val; break;
		case 0xFF41:
			lcdc_status = val; break;
		case 0xFF47:
			palette_bg_window = val; break;
		case 0xFF48:
			palette_obj_0 = val; break;
		case 0xFF49:
			palette_obj_1 = val; break;
		case 0xFF4A:
			window_y = val; break;
		case 0xFF4B:
			window_x = val; break;
	}
}

void GPU::cycle(){
	switch(lcdc_status & 0b11){
		case GPUMODE_HBLANK:
			if(m_timer->try_elapse_cycles(204)){
				line_y++;
				if(line_y == 144){
					set_gpumode(GPUMODE_VBLANK);
					m_mmu->set_interrupt_flag(INTR_VBLANK, 1);
					m_screen->draw(framebuffer);
				}else{
					set_gpumode(GPUMODE_OAM);
				}
			}
			break;
		case GPUMODE_VBLANK:
			if(m_timer->try_elapse_cycles(456)){
				line_y++;
				if(line_y == 154){
					line_y = 0;
					set_gpumode(GPUMODE_OAM);
				}
			}
			break;
		case GPUMODE_OAM:
			if(m_timer->try_elapse_cycles(80)){
				set_gpumode(GPUMODE_VRAM);
			}
			break;
		case GPUMODE_VRAM:
			if(m_timer->try_elapse_cycles(172)){
				set_gpumode(GPUMODE_HBLANK);

				if((lcd_control & LCDC_ENABLE_LCD) != 0){
					render_scanline();
				}
			}
			break;
	}
}

void GPU::render_scanline(){
	if((lcd_control & LCDC_ENABLE_BG_WINDOW) != 0)
		render_scanline_tiles();
	if((lcd_control & LCDC_ENABLE_SPRITE) != 0)
		render_scanline_sprites();
}

void GPU::render_scanline_tiles(){
	bool render_window = ((lcd_control & LCDC_ENABLE_WINDOW) != 0) && (window_y <= line_y);

	uint16_t addr_tiledata = ((lcd_control & LCDC_TILEDATA_BG_WINDOW) == 0)?0x8800:0x8000;
	uint16_t addr_tilemap;
	if(render_window)
		addr_tilemap = ((lcd_control & LCDC_TILEMAP_WINDOW) == 0)?0x9800:0x9C00;
	else
		addr_tilemap = ((lcd_control & LCDC_TILEMAP_BG) == 0)?0x9800:0x9C00;

	//vertical tile
	uint8_t tile_y = render_window?(line_y - window_y):(line_y + scroll_y);

	//vertical pixel of tile
	uint16_t tile_row = (tile_y >> 3) << 5;

	for(uint8_t p = 0; p < 160; p++){
		uint8_t tile_x = (render_window && p >= window_x)?(p - window_x):(p + scroll_x);

		uint16_t tile_col = tile_x >> 3;

		uint16_t addr_tile = addr_tilemap + tile_row + tile_col;

		//can be signed or unsigned
		uint8_t tile_id = m_mmu->read_byte(addr_tile);

		addr_tile = get_addr(addr_tiledata, tile_id, 16);

		uint8_t line = (tile_y & 0b111) << 1; //multiply by 2 (two bytes per line)

		uint8_t byte0 = m_mmu->read_byte(addr_tile + line);
		uint8_t byte1 = m_mmu->read_byte(addr_tile + line +1);

		//get pixel color index
		uint8_t bit_color = 0b111 - (tile_x & 0b111);
		uint8_t id_color = ((byte0 >> bit_color) & 1) | ((byte1 >> bit_color) << 1);
		uint8_t color = (palette_bg_window >> (id_color << 1)) & 3;

		framebuffer[p][line_y] = color;
	}
}

void GPU::render_scanline_sprites(){
	for(uint8_t s = 0; s < 40; s++){
		uint8_t sprite_index = s * 4; // 4 bytes per sprite
		
		uint8_t sprite_y = m_mmu->read_byte(0xFE00 + sprite_index) - 16;
		uint8_t sprite_x = m_mmu->read_byte(0xFE00 + sprite_index + 1) - 8;
		uint8_t tile_location = m_mmu->read_byte(0xFE00 + sprite_index + 2);
		uint8_t attr = m_mmu->read_byte(0xFE00 + sprite_index + 3);

		bool flip_y = (attr & 0b01000000) != 0;
		bool flip_x = (attr & 0b00100000) != 0;

		uint8_t size_y = ((lcd_control & LCDC_SIZE_SPRITE) == 0)?8:16;

		if((line_y >= sprite_y) && (line_y < (sprite_y + size_y))){
			uint8_t line = line_y - sprite_y;

			if(flip_y)
				line = (size_y - 1) - line;

			uint16_t addr_tile = (0x8000 + (tile_location << 4) + line);

			uint8_t byte0 = m_mmu->read_byte(addr_tile + line);
			uint8_t byte1 = m_mmu->read_byte(addr_tile + line +1);

			for(uint8_t p = 7; p >= 0; p--){
				uint8_t bit_color = p;
				
				if(flip_x)
					bit_color = 0b111 - (bit_color & 0b111);

				uint8_t id_color = ((byte0 >> bit_color) & 1) | ((byte1 >> bit_color) << 1);

				uint16_t addr_color = ((attr & 0b01000000) == 0)?0xFF48:0xFF49;
				uint8_t palette = m_mmu->read_byte(addr_color);
				
				uint8_t color = (palette >> (id_color << 1)) & 3;

				if(color == COLOR_WHITE) //transparent
					continue;

				uint8_t pixel = sprite_x + (0b111 - p);

				framebuffer[pixel][line_y] = color;
			}
		}
	}
}

uint16_t GPU::get_addr(uint16_t addr, uint8_t id, uint8_t size){
	//tile address
	if(addr == 0x8000)
		return addr + (id * size);
	return addr + ((((int8_t)id)+128) * size);
}

GPU::~GPU(){}

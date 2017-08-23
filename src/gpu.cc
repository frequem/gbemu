#include "gpu.hh"

GPU::GPU(){}

GPU::GPU(MMU *mmu, Screen *screen){
	Init(mmu, screen);
}

void GPU::Init(MMU *mmu, Screen *screen){
	m_mmu = mmu;
	m_screen = screen;
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
		case 0xFF42:
			return scroll_y;
		case 0xFF43:
			return scroll_x;
		case 0xFF40:
			return lcd_control;
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
		case 0xFF42:
			scroll_y = val; break;
		case 0xFF43:
			scroll_x = val; break;
		case 0xFF40:
			lcd_control = val; break;
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

void GPU::tick(){
	switch(lcdc_status & 0b11){
		case GPUMODE_HBLANK:
			line_y++;
			if(line_y == 144){
				set_gpumode(GPUMODE_VBLANK);
				m_mmu->set_interrupt_flag(INTR_VBLANK, 1);
			}else{
				set_gpumode(GPUMODE_OAM);
			}
			break;
		case GPUMODE_VBLANK:
			line_y++;
			if(line_y == 154){
				//write buffer, then draw
				line_y = 0;
				set_gpumode(GPUMODE_OAM);
			}
			break;
		case GPUMODE_OAM:
			set_gpumode(GPUMODE_VRAM);
			break;
		case GPUMODE_VRAM:
			set_gpumode(GPUMODE_HBLANK);
			break;
	}
}

GPU::~GPU(){}

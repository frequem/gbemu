#ifndef GPU_H
#define GPU_H

class GPU;

#include "memory.hh"
#include "mmu.hh"
#include "screen.hh"

const uint8_t LCDC_OPERATION_ENABLE = 	0b10000000;
const uint8_t LCDC_WINDOW_TILEMAP =		0b01000000;
const uint8_t LCDC_WINDOW_ENABLE =		0b00100000;
const uint8_t LCDC_TILEDATA = 			0b00010000;
const uint8_t LCDC_BG_TILEMAP = 		0b00001000;
const uint8_t LCDC_SPRITE_SIZE = 		0b00000100;
const uint8_t LCDC_SPRITE_ENABLE =		0b00000010;
const uint8_t LCDC_DISPLAY_ENABLE = 	0b00000001;

const uint8_t GPUMODE_HBLANK = 		0b00;
const uint8_t GPUMODE_VBLANK = 		0b01;
const uint8_t GPUMODE_OAM =			0b10;
const uint8_t GPUMODE_VRAM = 		0b11;

class GPU : public Memory{
public:
	GPU();
	GPU(MMU *mmu, Screen *screen);
	void Init(MMU *mmu, Screen *screen);
	~GPU();

	void reset();

	uint8_t read_byte(uint16_t addr);
	void write_byte(uint16_t addr, uint8_t val);

	void tick();
private:
	MMU *m_mmu;
	Screen *m_screen;

	void set_gpumode(uint8_t mode);

	uint8_t ram_video[0x2000];
	uint8_t oam[0xA0];

	uint8_t scroll_y; //FF42
	uint8_t scroll_x; //FF43
	uint8_t lcd_control; //FF40
	uint8_t line_y; //FF44
	uint8_t lcdc_status; //FF41
	uint8_t palette_bg_window; //FF47
	uint8_t palette_obj_0; //FF48
	uint8_t palette_obj_1; //FF49
	uint8_t window_y; //FF4A
	uint8_t window_x; //FF4B
};

#endif

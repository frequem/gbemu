#ifndef GPU_H
#define GPU_H

class GPU;

#include "mmu.hh"
#include "screen.hh"
#include "timer.hh"

const uint8_t LCDC_ENABLE_LCD = 		0b10000000;
const uint8_t LCDC_TILEMAP_WINDOW =		0b01000000;
const uint8_t LCDC_ENABLE_WINDOW =		0b00100000;
const uint8_t LCDC_TILEDATA_BG_WINDOW = 0b00010000;
const uint8_t LCDC_TILEMAP_BG = 		0b00001000;
const uint8_t LCDC_SIZE_SPRITE = 		0b00000100;
const uint8_t LCDC_ENABLE_SPRITE= 		0b00000010;
const uint8_t LCDC_ENABLE_BG_WINDOW = 	0b00000001;

const uint8_t STAT_INTR_LY_COINCIDENCE = 	0b01000000;
const uint8_t STAT_INTR_OAM = 				0b00100000;
const uint8_t STAT_INTR_VBLANK = 			0b00010000;
const uint8_t STAT_INTR_HBLANK = 			0b00001000;

const uint8_t STAT_LY_COINCIDENCE = 		0b00000100;

const uint8_t GPUMODE_HBLANK = 		0b00;
const uint8_t GPUMODE_VBLANK = 		0b01;
const uint8_t GPUMODE_OAM = 		0b10;
const uint8_t GPUMODE_VRAM = 		0b11;

const uint8_t COLOR_DMG_WHITE = 		0b00;
const uint8_t COLOR_DMG_LIGHT_GRAY = 	0b01;
const uint8_t COLOR_DMG_DARK_GRAY = 	0b10;
const uint8_t COLOR_DMG_BLACK = 		0b11;

const uint8_t SPRITE_FLIP_Y = 0b01000000;
const uint8_t SPRITE_FLIP_X = 0b00100000;

const uint8_t COLORS_DMG[4][3] = {
	{0xFF, 0xFF, 0xFF},
	{0xCC, 0xCC, 0xCC},
	{0x77, 0x77, 0x77},
	{0x00, 0x00, 0x00}
};

const uint16_t CYCLES_OAM = 	80;
const uint16_t CYCLES_VRAM = 	172;
const uint16_t CYCLES_HBLANK = 	204;
const uint16_t CYCLES_VBLANK =	CYCLES_OAM + CYCLES_VRAM + CYCLES_HBLANK;

class GPU{
public:
	GPU();
	GPU(MMU *mmu, Screen *screen, Timer *timer);
	void Init(MMU *mmu, Screen *screen, Timer *timer);
	~GPU();

	void reset();

	void cycle();
private:
	MMU *m_mmu;
	Screen *m_screen;
	Timer *m_timer;

	uint64_t m_gpu_cycles;

	void set_gpumode(uint8_t mode, bool set_interrupt);
	
	void render_scanline();
	
	void render_scanline_tiles();
	void render_scanline_sprites();

	static uint16_t get_addr_tiledata(uint16_t addr, uint8_t id, uint8_t size);
	static uint8_t* get_color_dmg(uint8_t id, uint8_t palette);
	
	uint8_t screenbuffer[144][160][3];
};

#endif

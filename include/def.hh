#ifndef DEF_H
#define DEF_H

#include <cstdint>
#include <map>

const uint8_t MODE_DMG = 0;

const uint8_t FPS = 60;

const uint32_t CLOCK_SPEED_DMG = 4194304;
const uint32_t FRAMECYCLES_DMG = CLOCK_SPEED_DMG / FPS;

const uint16_t CYCLES_OAM = 	80;
const uint16_t CYCLES_VRAM = 	172;
const uint16_t CYCLES_HBLANK = 	204;
const uint16_t CYCLES_VBLANK =	CYCLES_OAM + CYCLES_VRAM + CYCLES_HBLANK;

const uint16_t ADDR_ROMBANK_0_START = 0x0000;

const uint16_t ADDR_CARTRIDGE_TYPE = 0x0147;

const uint8_t CARTRIDGE_TYPE_ROM_ONLY = 			0;
const uint8_t CARTRIDGE_TYPE_ROM_MBC1 = 			1;
const uint8_t CARTRIDGE_TYPE_ROM_MBC1_RAM = 		2;
const uint8_t CARTRIDGE_TYPE_ROM_MBC1_RAM_BATT = 	3;
const uint8_t CARTRIDGE_TYPE_ROM_MBC2 = 			5;
const uint8_t CARTRIDGE_TYPE_ROM_MBC2_BATT = 		6;

const uint16_t ADDR_ROM_SIZE = 0x0148;

const std::map<uint8_t, uint8_t> ROM_SIZE_MAP = {
	{0, 2},
	{1, 4},
	{2, 8},
	{3, 16},
	{4, 32},
	{5, 64},
	{6, 128},
	{0x52, 72},
	{0x53, 80},
	{0x54, 96}
};

const uint16_t ADDR_RAM_SIZE = 0x0149;

const std::map<uint8_t, uint8_t> RAM_SIZE_MAP = {
	{0, 0},
	{1, 1},
	{2, 1},
	{3, 4},
	{4, 16},
};

const uint16_t ADDR_ROMBANK_1_START = 0x4000;

const uint16_t ADDR_OAM_START = 				0xFE00;

const uint8_t SPRITE_FLAG_PRIORITY = 		0b10000000; // 0.. on top of bg & window, else: below
const uint8_t SPRITE_FLAG_FLIP_Y = 			0b01000000;
const uint8_t SPRITE_FLAG_FLIP_X = 			0b00100000;
const uint8_t SPRITE_FLAG_PALETTE_ID = 		0b00001000;
const uint8_t SPRITE_FLAG_PALETTE_ID_MASK = 0b00000111; //id in color palette (cgb only)

const uint16_t SPRITE_COLOR_RED = 	0b0000000000011111;
const uint16_t SPRITE_COLOR_GREEN = 0b0000001111100000;
const uint16_t SPRITE_COLOR_BLUE = 	0b0111110000000000;

const uint16_t ADDR_JOYPAD_INFO = 				0xFF00;

const uint8_t JOYPAD_OUT_DIRECTIONS = 	0b00100000;
const uint8_t JOYPAD_OUT_BUTTONS =		0b00010000;

const uint8_t JOYPAD_IN_DOWN_START = 	0b00001000;
const uint8_t JOYPAD_IN_UP_SELECT =		0b00000100;
const uint8_t JOYPAD_IN_LEFT_B =		0b00000010;
const uint8_t JOYPAD_IN_RIGHT_A =		0b00000001;

const uint8_t BUTTON_RIGHT = 	0b00000001;
const uint8_t BUTTON_LEFT = 	0b00000010;
const uint8_t BUTTON_UP = 		0b00000100;
const uint8_t BUTTON_DOWN = 	0b00001000;
const uint8_t BUTTON_A = 		0b00010000;
const uint8_t BUTTON_B = 		0b00100000;
const uint8_t BUTTON_SELECT = 	0b01000000;
const uint8_t BUTTON_START = 	0b10000000;

const uint16_t ADDR_SERIAL_TRANSFER_DATA = 		0xFF01;
const uint16_t ADDR_SIO_CONTROL = 				0xFF02;
const uint16_t ADDR_DIVIDER_REGISTER = 			0xFF04;

const uint32_t CLOCK_FREQUENCY_DIV = 16382;

const uint16_t ADDR_TIMER_COUNTER = 			0xFF05;
const uint16_t ADDR_TIMER_MODULO = 				0xFF06;
const uint16_t ADDR_TIMER_CONTROL = 			0xFF07;

const uint8_t TAC_TIMER_ENABLE = 0b100;
const uint8_t TAC_CLOCK_SELECT = 0b011;

const uint32_t CLOCK_FREQUENCIES[4] = {
	4096,
	262144,
	65536,
	16382
};

const uint16_t ADDR_INTERRUPT_FLAG = 			0xFF0F;

const uint8_t INTR_VBLANK = 0b00000001;
const uint8_t INTR_LCDC = 	0b00000010;
const uint8_t INTR_TIMER =	0b00000100;
const uint8_t INTR_SERIAL =	0b00001000;
const uint8_t INTR_JOYPAD = 0b00010000;

const uint16_t ADDR_LCD_CONTROL = 				0xFF40;

const uint8_t LCDC_ENABLE_LCD = 		0b10000000;
const uint8_t LCDC_TILEMAP_WINDOW =		0b01000000;
const uint8_t LCDC_ENABLE_WINDOW =		0b00100000;
const uint8_t LCDC_TILEDATA_BG_WINDOW = 0b00010000;
const uint8_t LCDC_TILEMAP_BG = 		0b00001000;
const uint8_t LCDC_SIZE_SPRITE = 		0b00000100;
const uint8_t LCDC_ENABLE_SPRITE= 		0b00000010;
const uint8_t LCDC_ENABLE_BG_WINDOW = 	0b00000001;

const uint16_t ADDR_LCDC_STATUS = 				0xFF41;

const uint8_t STAT_INTR_LY_COINCIDENCE = 	0b01000000;
const uint8_t STAT_INTR_OAM = 				0b00100000;
const uint8_t STAT_INTR_VBLANK = 			0b00010000;
const uint8_t STAT_INTR_HBLANK = 			0b00001000;
const uint8_t STAT_LY_COINCIDENCE = 		0b00000100;

const uint8_t GPUMODE_HBLANK = 				0b00000000;
const uint8_t GPUMODE_VBLANK = 				0b00000001;
const uint8_t GPUMODE_OAM = 				0b00000010;
const uint8_t GPUMODE_VRAM = 				0b00000011;

const uint16_t ADDR_SCROLL_Y = 					0xFF42;
const uint16_t ADDR_SCROLL_X = 					0xFF43;
const uint16_t ADDR_LCDC_Y_COORD = 				0xFF44;
const uint16_t ADDR_LY_COMPARE = 				0xFF45;
const uint16_t ADDR_DMA_TRANSFER_ADDR = 		0xFF46;
const uint16_t ADDR_BG_WINDOW_PALETTE_DATA = 	0xFF47;
const uint16_t ADDR_OBJECT_PALETTE_0_DATA = 	0xFF48;
const uint16_t ADDR_OBJECT_PALETTE_1_DATA = 	0xFF49;

const uint8_t COLOR_DMG_WHITE = 		0b00;
const uint8_t COLOR_DMG_LIGHT_GRAY = 	0b01;
const uint8_t COLOR_DMG_DARK_GRAY = 	0b10;
const uint8_t COLOR_DMG_BLACK = 		0b11;

const uint8_t COLORS_DMG[4][3] = {
	{0xFF, 0xFF, 0xFF},
	{0xCC, 0xCC, 0xCC},
	{0x77, 0x77, 0x77},
	{0x00, 0x00, 0x00}
};

const uint16_t ADDR_WINDOW_Y_POS = 				0xFF4A;
const uint16_t ADDR_WINDOW_X_POS = 				0xFF4B;

const uint16_t ADDR_BG_COLOR_PALETTE_SPEC = 	0xFF68;
const uint16_t ADDR_BG_COLOR_PALETTE_DATA = 	0xFF69;
const uint16_t ADDR_OBJECT_COLOR_PALETTE_SPEC = 0xFF6A;
const uint16_t ADDR_OBJECT_COLOR_PALETTE_DATA = 0xFF6B;

const uint8_t COLOR_PALETTE_SPEC_DATAINDEX = 		0b00111111;
const uint8_t COLOR_PALETTE_SPEC_AUTOINCREMENT = 	0b10000000;

const uint16_t ADDR_INTERRUPT_ENABLE = 			0xFFFF;


const uint8_t FLAG_ZERO =		0b10000000;
const uint8_t FLAG_SUBTRACT =	0b01000000;
const uint8_t FLAG_HALF_CARRY =	0b00100000;
const uint8_t FLAG_CARRY =		0b00010000;

const int OP_CYCLES[0x100] = {
	4,  12, 8,  8,  4,  4,  8,  4,  20, 8,  8,  8, 4,  4,  8, 4,
	4,  12, 8,  8,  4,  4,  8,  4,  12, 8,  8,  8, 4,  4,  8, 4,
	8,  12, 8,  8,  4,  4,  8,  4,  8,  8,  8,  8, 4,  4,  8, 4,
	8,  12, 8,  8,  12, 12, 12, 4,  8,  8,  8,  8, 4,  4,  8, 4,
	4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4, 4,  4,  8, 4,
	4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4, 4,  4,  8, 4,
	4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4, 4,  4,  8, 4,
	8,  8,  8,  8,  8,  8,  4,  8,  4,  4,  4,  4, 4,  4,  8, 4,
	4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4, 4,  4,  8, 4,
	4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4, 4,  4,  8, 4,
	4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4, 4,  4,  8, 4,
	4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4, 4,  4,  8, 4,
	8,  12, 12, 16, 12, 16, 8,  16, 8,  16, 12, 4, 12, 24, 8, 16,
	8,  12, 12, 0,  12, 16, 8,  16, 8,  16, 12, 0, 12, 0,  8, 16,
	12, 12, 8,  0,  0,  16, 8,  16, 16, 4,  16, 0, 0,  0,  8, 16,
	12, 12, 8,  4,  0,  16, 8,  16, 12, 8,  16, 4, 0,  0,  8, 16,
};

const int OP_CYCLES_CB[0x10] = {
	8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8
};

#endif

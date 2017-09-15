#ifndef MMU_H
#define MMU_H

class MMU;

#include "cartridge.hh"
#include <cstdint>
#include <istream>

const uint8_t INTR_VBLANK = 0b00000001;
const uint8_t INTR_LCDC = 	0b00000010;
const uint8_t INTR_TIMER =	0b00000100;
const uint8_t INTR_SERIAL =	0b00001000;
const uint8_t INTR_JOYPAD = 0b00010000;

const uint16_t ADDR_ROMBANK_0_START = 0x0000;
const uint16_t ADDR_ROMBANK_1_START = 0x4000;

const uint16_t ADDR_JOYPAD_INFO = 				0xFF00;
const uint16_t ADDR_SERIAL_TRANSFER_DATA = 		0xFF01;
const uint16_t ADDR_SIO_CONTROL = 				0xFF02;
const uint16_t ADDR_DIVIDER_REGISTER = 			0xFF04;
const uint16_t ADDR_TIMER_COUNTER = 			0xFF05;
const uint16_t ADDR_TIMER_MODULO = 				0xFF06;
const uint16_t ADDR_TIMER_CONTROL = 			0xFF07;
const uint16_t ADDR_INTERRUPT_FLAG = 			0xFF0F;

const uint16_t ADDR_LCD_CONTROL = 				0xFF40;
const uint16_t ADDR_LCDC_STATUS = 				0xFF41;
const uint16_t ADDR_SCROLL_Y = 					0xFF42;
const uint16_t ADDR_SCROLL_X = 					0xFF43;
const uint16_t ADDR_LCDC_Y_COORD = 				0xFF44;
const uint16_t ADDR_LY_COMPARE = 				0xFF45;
const uint16_t ADDR_DMA_TRANSFER_ADDR = 		0xFF46;
const uint16_t ADDR_BG_WINDOW_PALETTE_DATA = 	0xFF47;
const uint16_t ADDR_OBJECT_PALETTE_0_DATA = 	0xFF48;
const uint16_t ADDR_OBJECT_PALETTE_1_DATA = 	0xFF49;
const uint16_t ADDR_WINDOW_Y_POS = 				0xFF4A;
const uint16_t ADDR_WINDOW_X_POS = 				0xFF4B;
const uint16_t ADDR_INTERRUPT_ENABLE = 			0xFFFF;


class MMU{
public:
	MMU();
	~MMU();

	void reset();

	void increment(uint16_t addr);
	
	void write_bit(uint16_t addr, uint8_t bitmask, bool set);
	bool read_bit(uint16_t addr, uint8_t bitmask);

	uint8_t read_byte(uint16_t addr);
	void write_byte(uint16_t addr, uint8_t val);
	
	uint16_t read_word(uint16_t addr);
	void write_word(uint16_t addr, uint16_t val);

	void write_stream(uint16_t addr_start, std::istream& stream, uint32_t length);
	
private:
	void dma_transfer(uint16_t addr_source);

	uint8_t m_memory[0x10000];
};

#endif

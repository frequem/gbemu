#include "mmu.hh"
#include <iostream>

MMU::MMU(){
	reset();
}

void MMU::reset(){
	m_memory[ADDR_TIMER_COUNTER] = 0;
	m_memory[ADDR_TIMER_MODULO] = 0;
	m_memory[ADDR_TIMER_CONTROL] = 0;
	
	m_memory[ADDR_LCD_CONTROL] = 0x91;
	m_memory[ADDR_SCROLL_Y] = 0;
	m_memory[ADDR_SCROLL_X] = 0;
	m_memory[ADDR_BG_WINDOW_PALETTE_DATA] = 0xFC;
	m_memory[ADDR_OBJECT_PALETTE_0_DATA] = 0xFF;
	m_memory[ADDR_OBJECT_PALETTE_1_DATA] = 0xFF;
	m_memory[ADDR_WINDOW_Y_POS] = 0;
	m_memory[ADDR_WINDOW_X_POS] = 0;
	m_memory[ADDR_LCDC_Y_COORD] = 0;
	m_memory[ADDR_LY_COMPARE] = 0;
	
	m_memory[ADDR_JOYPAD_INFO] = 0b11001111;
	m_memory[ADDR_INTERRUPT_ENABLE] = 0;
}

void MMU::write_bit(uint16_t addr, uint8_t bitmask, bool set){
	m_memory[addr] &= (~bitmask);
	if(set) m_memory[addr] |= bitmask;
}

bool MMU::read_bit(uint16_t addr, uint8_t bitmask){
	return (m_memory[addr] & bitmask) == bitmask;
}

void MMU::increment(uint16_t addr){
	m_memory[addr]++;
}

uint8_t MMU::read_byte(uint16_t addr){
	return m_memory[addr];
}

void MMU::write_byte(uint16_t addr, uint8_t val){
	if(addr < 0x8000) //cartridge is read only
		return;
	if((addr >= 0xE000) && (addr < 0xFE00)) //write to echo ram
		write_byte(addr - 0x2000, val);
	if((addr >= 0xFEA0) && (addr < 0xFEFF)) // restricted
		return;

	

	switch(addr){ //writing will reset
		case ADDR_LCDC_Y_COORD:
		case ADDR_DIVIDER_REGISTER:
			val = 0; break;
		case ADDR_DMA_TRANSFER_ADDR:
			dma_transfer(((uint16_t)val) << 8); return;
		case ADDR_JOYPAD_INFO:
			m_memory[ADDR_JOYPAD_INFO] |= (val & 0b00110000);
			return; // for now
	}
	
	m_memory[addr] = val;
}

void MMU::dma_transfer(uint16_t addr_source){
	for(uint16_t i = 0; i < 160; i++){
		write_byte(0xFE00 + i, read_byte(addr_source + i));
	}
}

uint16_t MMU::read_word(uint16_t addr){
	return (read_byte(addr+1)<<8 | read_byte(addr));
}

void MMU::write_word(uint16_t addr, uint16_t val){
	write_byte(addr, val & 0xFF);
	write_byte(addr+1, val >> 8);
}

void MMU::write_stream(uint16_t addr_start, std::istream& stream, uint32_t length){
	stream.read((char*)(m_memory + (addr_start * sizeof(uint8_t))), length);
}

MMU::~MMU(){
}

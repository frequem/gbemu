#include "mmu.hh"
#include <iostream>

MMU::MMU(uint8_t mode){
	m_mode = mode;
	reset();
}

void MMU::reset(){
	*get_byte(ADDR_TIMER_COUNTER) = 0;
	*get_byte(ADDR_TIMER_MODULO) = 0;
	*get_byte(ADDR_TIMER_CONTROL) = 0;
	
	*get_byte(ADDR_LCD_CONTROL) = 0x91;
	*get_byte(ADDR_SCROLL_Y) = 0;
	*get_byte(ADDR_SCROLL_X) = 0;
	*get_byte(ADDR_BG_WINDOW_PALETTE_DATA) = 0xFC;
	*get_byte(ADDR_OBJECT_PALETTE_0_DATA) = 0xFF;
	*get_byte(ADDR_OBJECT_PALETTE_1_DATA) = 0xFF;
	*get_byte(ADDR_WINDOW_Y_POS) = 0;
	*get_byte(ADDR_WINDOW_X_POS) = 0;
	*get_byte(ADDR_LCDC_Y_COORD) = 0;
	*get_byte(ADDR_LY_COMPARE) = 0;
	
	*get_byte(ADDR_JOYPAD_INFO) = 0b11001111;
	*get_byte(ADDR_INTERRUPT_ENABLE) = 0;
}

void MMU::allocate_rombanks(uint8_t banks){
	if(banks == 0) return;
	m_rombanks = new uint8_t[banks*0x4000];
}

void MMU::init_rombank(uint8_t bank, std::istream& stream){
	stream.read((char*)(m_rombanks + (bank * 0x4000 * sizeof(uint8_t))), 0x4000);
}

void MMU::allocate_rambanks(uint8_t banks){
	if(banks == 0) return;
	m_rambanks = new uint8_t[banks*0x2000];
}

uint8_t* MMU::get_byte(uint16_t addr){
	if(addr < 0x8000)
		return &m_rombanks[addr];
	if((addr < 0xC000) && (addr >= 0xA000))
		return &m_rambanks[addr - 0xA000];
		
	return &m_memory[addr - 0x8000];
}

uint8_t MMU::read_byte(uint16_t addr){
	return *get_byte(addr);
}

void MMU::write_byte(uint16_t addr, uint8_t val){
	if(addr < 0x8000){
		return;
	}
	
	if((addr >= 0xE000) && (addr < 0xFE00)) //write to echo ram
		write_byte(addr - 0x2000, val);
	if((addr >= 0xFEA0) && (addr < 0xFEFF)) // restricted
		return;

	switch(addr){
		case ADDR_LCDC_Y_COORD:
		case ADDR_DIVIDER_REGISTER:
			val = 0; break; //writing will reset
		case ADDR_DMA_TRANSFER_ADDR:
			dma_transfer(((uint16_t)val) << 8); return;
	}
	*get_byte(addr) = val;
}

uint16_t MMU::read_word(uint16_t addr){
	return (read_byte(addr+1)<<8 | read_byte(addr));
}

void MMU::write_word(uint16_t addr, uint16_t val){
	write_byte(addr, val & 0xFF);
	write_byte(addr+1, val >> 8);
}

bool MMU::read_bit(uint16_t addr, uint8_t bitmask){
	return (*get_byte(addr) & bitmask) == bitmask;
}

void MMU::write_bit(uint16_t addr, uint8_t bitmask, bool set){
	uint8_t* b = get_byte(addr);
	(*b) &= (~bitmask);
	if(set) (*b) |= bitmask;
}

void MMU::increment(uint16_t addr){
	(*get_byte(addr))++;
}

void MMU::handle_banking(uint16_t addr, uint8_t val){
}

void MMU::dma_transfer(uint16_t addr_source){
	for(uint16_t i = 0; i < 160; i++){
		*get_byte(ADDR_OAM_START + i) = read_byte(addr_source + i);
	}
}

MMU::~MMU(){
	if(m_rombanks) delete [] m_rombanks;
	if(m_rambanks) delete [] m_rambanks;
}

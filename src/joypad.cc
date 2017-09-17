#include "joypad.hh"

Joypad::Joypad(){}

void Joypad::InitInternal(MMU *mmu){
	m_mmu = mmu;
}

void Joypad::set_buttons(uint8_t buttons){
	uint8_t info = m_mmu->read_byte(ADDR_JOYPAD_INFO);
	
	uint8_t out = (~info) & (OUT_DIRECTIONS | OUT_BUTTONS);
	if(info & OUT_BUTTONS){
		buttons >>= 4;
	}
	out |= buttons & 0b1111;
	
	m_mmu->write_byte(ADDR_JOYPAD_INFO, ~out);
}

Joypad::~Joypad(){}


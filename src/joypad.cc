#include "joypad.hh"

Joypad::Joypad(){
	buttons = 0;
}

uint8_t Joypad::read_byte(uint16_t addr){
	if(addr == 0xFF00){
		return buttons & 0xF;
	}
	return 0;
}

void Joypad::write_byte(uint16_t addr, uint8_t val){
	if(addr == 0xFF00){
		buttons |= (val & (OUT_BUTTONS | OUT_DIRECTIONS));
	}
}


Joypad::~Joypad(){}


#include "joypad.hh"

Joypad::Joypad(){
	//buttons = 0b11001111;
}

void Joypad::InitInternal(MMU *mmu){
	m_mmu = mmu;
}

Joypad::~Joypad(){}


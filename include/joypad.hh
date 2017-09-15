#ifndef JOYPAD_H
#define JOYPAD_H

class Joypad;

#include "mmu.hh"
#include <cstdint>

const uint8_t OUT_DIRECTIONS = 	0b00100000;
const uint8_t OUT_BUTTONS =		0b00010000;

const uint8_t IN_DOWN_START = 	0b00001000;
const uint8_t IN_UP_SELECT =	0b00000100;
const uint8_t IN_LEFT_B =		0b00000010;
const uint8_t IN_RIGHT_A =		0b00000001;

class Joypad{
public:
	Joypad();
	void InitInternal(MMU *m_mmu);
	~Joypad();
private:
	MMU *m_mmu;
};

#endif

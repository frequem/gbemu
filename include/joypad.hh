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

const uint8_t BUTTON_RIGHT = 	0b00000001;
const uint8_t BUTTON_LEFT = 	0b00000010;
const uint8_t BUTTON_UP = 		0b00000100;
const uint8_t BUTTON_DOWN = 	0b00001000;
const uint8_t BUTTON_A = 		0b00010000;
const uint8_t BUTTON_B = 		0b00100000;
const uint8_t BUTTON_SELECT = 	0b01000000;
const uint8_t BUTTON_START = 	0b10000000;

class Joypad{
public:
	Joypad();
	void InitInternal(MMU *m_mmu);
	~Joypad();

	virtual void cycle() = 0;
protected:
	void set_buttons(uint8_t buttons);
private:
	MMU *m_mmu;
};

#endif

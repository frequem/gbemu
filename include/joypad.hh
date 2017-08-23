#ifndef JOYPAD_H
#define JOYPAD_H

class Joypad;

#include "memory.hh"

const uint8_t OUT_DIRECTIONS = 	0b00100000;
const uint8_t OUT_BUTTONS =		0b00010000;

const uint8_t IN_DOWN_START = 	0b00001000;
const uint8_t IN_UP_SELECT =	0b00000100;
const uint8_t IN_LEFT_B =		0b00000010;
const uint8_t IN_RIGHT_A =		0b00000001;

class Joypad : public Memory{
	public:
		Joypad();
		~Joypad();

		uint8_t read_byte(uint16_t addr);
		void write_byte(uint16_t addr, uint8_t val);
	private:
		uint8_t buttons;
		
};

#endif

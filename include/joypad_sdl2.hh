#ifndef JOYPAD_SDL2_H
#define JOYPAD_SDL2_H

#include "joypad.hh"
#include <iostream>
#include <SDL2/SDL.h>

class SDL2Joypad: public Joypad{
public:
	SDL2Joypad();
	~SDL2Joypad();

	void cycle();
private:
	const Uint8 *keys;
};

#endif

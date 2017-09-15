#ifndef SCREEN_NONE_H
#define SCREEN_NONE_H

#include "screen.hh"

class NoneScreen : public Screen{
public:
	NoneScreen();
	void render(uint8_t screenbuffer[160][144][3]);
	void draw();
	bool enabled();
};

#endif

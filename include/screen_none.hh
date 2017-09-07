#ifndef SCREEN_NONE_H
#define SCREEN_NONE_H

#include "screen.hh"

class NoneScreen : public Screen{
public:
	void draw(uint8_t framebuffer[160][144]);
	bool enabled();
};

#endif

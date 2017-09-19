#ifndef SCREEN_H
#define SCREEN_H

#include "def.hh"

class Screen{
public:
	virtual void render(uint8_t screenbuffer[144][160][3]) = 0;
	virtual void draw() = 0;
	virtual bool enabled() = 0;
	virtual ~Screen(){}
};

#endif

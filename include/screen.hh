#ifndef SCREEN_H
#define SCREEN_H

#include <cstdint>

class Screen{
public:
	virtual void draw(uint8_t framebuffer[160][144]) = 0;
	virtual ~Screen(){}
};

#endif

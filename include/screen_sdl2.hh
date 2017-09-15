#ifndef SCREEN_SDL2_H
#define SCREEN_SDL2_H

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "screen.hh"
#include <cstring>

class SDL2Screen : public Screen{
public:
	SDL2Screen(uint16_t width = 160*3, uint16_t height = 144*3);
	~SDL2Screen();
	void render(uint8_t screenbuffer[144][160][3]);
	void draw();
	bool enabled();
private:
	uint16_t m_width, m_height;
	SDL_Window *win;
	SDL_GLContext context;

	uint8_t framebuffer[144][160][3];
	
	bool running;
};

#endif

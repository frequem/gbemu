#ifndef SCREEN_SDL2_H
#define SCREEN_SDL2_H

#include <SDL2/SDL.h>
#include "screen.hh"

class SDL2Screen : public Screen{
public:
	SDL2Screen(uint16_t width = 200, uint16_t height = 200);
	~SDL2Screen();
	void draw(uint8_t framebuffer[160][144]);
	bool enabled();
private:
	SDL_Window *win;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_Event *event;
	
	bool running;
};

#endif

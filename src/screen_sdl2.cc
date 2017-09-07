#include "screen_sdl2.hh"
#include "gpu.hh"
#include <iostream>
#include <unistd.h>

SDL2Screen::SDL2Screen(uint16_t width, uint16_t height){
	running = true;
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		running = false;
		return;
	}

	win = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
	if (win == nullptr){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		running = false;
		return;
	}
	
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == nullptr){
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		running = false;
		return;
	}

	texture = SDL_CreateTexture(renderer, SDL_GetWindowPixelFormat(win), SDL_TEXTUREACCESS_STREAMING, 256, 256);
	if(texture == nullptr){
		std::cout << "SDL_CreateTexture Error: " << SDL_GetError() << std::endl;
		running = false;
		return;
	}

	event = new SDL_Event();
	
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void SDL2Screen::draw(uint8_t framebuffer[160][144]){
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

bool SDL2Screen::enabled(){
	usleep(100); //awful hack until timing is implemented
	while(SDL_PollEvent(event)){
		if (event->type == SDL_QUIT) {
			running = false;
		}
	}
	return running;
}

SDL2Screen::~SDL2Screen(){
	if(event) delete event;
	if(texture) SDL_DestroyTexture(texture);
	if(renderer) SDL_DestroyRenderer(renderer);
	if(win) SDL_DestroyWindow(win);
	SDL_Quit();
}

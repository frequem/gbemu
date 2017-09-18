#include "screen_sdl2.hh"
#include "gpu.hh"
#include <iostream>
#include <unistd.h>

SDL2Screen::SDL2Screen(uint16_t width, uint16_t height){
	m_width = width;
	m_height = height;
	running = true;
	
	std::memset(&framebuffer, 0xFF, 160 * 144 * 3 * sizeof(uint8_t));
	
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		running = false;
		return;
	}
	
	win = SDL_CreateWindow("gbemu - SDL2Screen", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
	if (win == nullptr){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		running = false;
		return;
	}

	context = SDL_GL_CreateContext(win);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);
	
	glewInit();

	glViewport(0, 0, width, height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -1.0, 1.0);
	glClearColor(0, 0, 0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_FLAT);

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DITHER);
	glDisable(GL_BLEND);
	
	SDL_GL_SwapWindow(win);
}

void SDL2Screen::render(uint8_t screenbuffer[144][160][3]){
	std::memcpy(&framebuffer, screenbuffer, 144 * 160 * 3 * sizeof(uint8_t));
}

void SDL2Screen::draw(){
 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 	glLoadIdentity();
 	glRasterPos2i(-1, 1);
	glPixelZoom(m_width/160., -m_height/144.);
 	glDrawPixels(160, 144, GL_RGB, GL_UNSIGNED_BYTE, framebuffer);
	SDL_GL_SwapWindow(win) ;
}

bool SDL2Screen::enabled(){
	return !SDL_QuitRequested();
}


SDL2Screen::~SDL2Screen(){
	if(context) SDL_GL_DeleteContext(context);
	if(win) SDL_DestroyWindow(win);
	SDL_Quit();
}

#include "joypad_sdl2.hh"

SDL2Joypad::SDL2Joypad(){
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return;
	}
	
	keys = SDL_GetKeyboardState(NULL);
}

void SDL2Joypad::cycle(){
	SDL_PumpEvents(); //doesn't interfere with sdl-screen since event queue is only updated
	uint8_t buttons = 0;
	
	if(keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W])
		buttons |= BUTTON_UP;
	if(keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A])
		buttons |= BUTTON_LEFT;
	if(keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S])
		buttons |= BUTTON_DOWN;
	if(keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D])
		buttons |= BUTTON_RIGHT;
	if(keys[SDL_SCANCODE_N])
		buttons |= BUTTON_SELECT;
	if(keys[SDL_SCANCODE_J])
		buttons |= BUTTON_B;
	if(keys[SDL_SCANCODE_M])
		buttons |= BUTTON_START;
	if(keys[SDL_SCANCODE_K])
		buttons |= BUTTON_A;
		
	set_buttons(buttons);
}

SDL2Joypad::~SDL2Joypad(){
	SDL_Quit();
}


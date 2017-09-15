#include "gameboy.hh"
#include "cartridge.hh"
#include "screen_none.hh"
#include "screen_sdl2.hh"
#include "joypad.hh"
#include <iostream>

int main(int argc, char* argv[]){
	if(argc < 2){
		std::cerr << "Usage: " << argv[0] << " <rom.gb>" << std::endl;
		return 1;
	}
	Cartridge cart(argv[1]);
	SDL2Screen screen;
	Joypad joypad;
	Gameboy gb(&cart, &screen, &joypad);

	gb.run();
	
	return 0;
}

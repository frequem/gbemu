#include "gameboy.hh"
#include "cartridge.hh"
#include "screen_none.hh"
#include "screen_sdl2.hh"
#include "joypad.hh"

int main(){
	Cartridge cart("tetris.gb");
	SDL2Screen screen;
	Joypad joypad;
	Gameboy gb(&cart, &screen, &joypad);

	gb.run();
	
	return 0;
}

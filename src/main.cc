#include "gameboy.hh"
#include "cartridge.hh"
#include "screen.hh"
#include "joypad.hh"

int main(){
	Cartridge cart("tetris.gb");
	Screen screen;
	Joypad joypad;
	Gameboy gb(&cart, &screen, &joypad);

	for(;;){
		gb.tick();
	}
	
	return 0;
}

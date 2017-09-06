#include "gameboy.hh"
#include "cartridge.hh"
#include "screen_none.hh"
#include "joypad.hh"

int main(){
	Cartridge cart("tetris.gb");
	NoneScreen screen;
	Joypad joypad;
	Gameboy gb(&cart, &screen, &joypad);

	for(;;){
		gb.tick();
	}
	
	return 0;
}

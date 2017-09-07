#include "screen_none.hh"
#include "gpu.hh"
#include <iostream>

void NoneScreen::draw(uint8_t framebuffer[160][144]){
	for(int x = 0; x < 160; x++){
		for(int y = 0; y < 144; y++){
			if(framebuffer[x][y] != COLOR_WHITE)
				std::cout << "" << x << "," << y << ":" << (int)framebuffer[x][y] << std::endl;
		}
	}
}

bool NoneScreen::enabled(){
	return true;
}

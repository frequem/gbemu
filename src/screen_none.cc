#include "screen_none.hh"
#include "gpu.hh"
#include <iostream>

NoneScreen::NoneScreen(){
}

void NoneScreen::render(uint8_t screenbuffer[160][144][3]){
	for(int x = 0; x < 160; x++){
		for(int y = 0; y < 144; y++){
		}
	}
}

void NoneScreen::draw(){
}

bool NoneScreen::enabled(){
	return true;
}

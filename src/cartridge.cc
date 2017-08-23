#include "cartridge.hh"
#include <fstream>
#include <iostream>

Cartridge::Cartridge(){}

Cartridge::Cartridge(const std::string& fname){
	Init(fname);
}

void Cartridge::Init(const std::string& fname){
	load(fname);
}

void Cartridge::load(const std::string& fname){
	std::ifstream file(fname.c_str(), std::ifstream::in | std::ifstream::binary);

	if(!file.is_open()){
		std::cout << "Error opening " << fname << std::endl;
		return;
	}
	
	file.seekg(0x0);
	file.read((char*)rombank_0, 0x4000);
	file.read((char*)rombank_1, 0x4000);

	file.close();

}

uint8_t Cartridge::read_byte(uint16_t addr){
	if(addr < 0x4000){
		return rombank_0[addr];
	}else if(addr < 0x8000){
		return rombank_1[addr & 0x3FFF];
	}else if(addr < 0xC000){
		return ram_external[addr & 0x1FFF];
	}
	return 0;
}

void Cartridge::write_byte(uint16_t addr, uint8_t val){
	if(addr < 0x4000){
		rombank_0[addr] = val;
	}else if(addr < 0x8000){
		rombank_1[addr & 0x3FFF] = val;
	}else if(addr < 0xC000){
		ram_external[addr & 0x1FFF] = val;
	}
}


Cartridge::~Cartridge(){}

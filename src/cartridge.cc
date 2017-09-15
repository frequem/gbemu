#include "cartridge.hh"
#include <fstream>
#include <iostream>

Cartridge::Cartridge(){}

Cartridge::Cartridge(const std::string& fname){
	Init(fname);
}

void Cartridge::Init(const std::string& fname){
	m_fname = fname;
}

void Cartridge::InitInternal(MMU *mmu){
	m_mmu = mmu;
	load(m_fname);
}

void Cartridge::load(const std::string& fname){
	std::ifstream file(fname.c_str(), std::ifstream::in | std::ifstream::binary);

	if(!file.is_open()){
		std::cout << "Error opening " << fname << std::endl;
		return;
	}
	
	file.seekg(0x0);
	m_mmu->write_stream(ADDR_ROMBANK_0_START, file, 0x4000);
	m_mmu->write_stream(ADDR_ROMBANK_1_START, file, 0x4000);

	file.close();
}

Cartridge::~Cartridge(){}

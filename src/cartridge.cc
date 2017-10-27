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
	
	file.seekg(ADDR_ROM_SIZE);
	uint8_t rombanks = ROM_SIZE_MAP.at(file.peek());
	m_mmu->allocate_rombanks(rombanks);
	
	file.seekg(ADDR_RAM_SIZE);
	m_mmu->allocate_rambanks(RAM_SIZE_MAP.at(file.peek()));
	
	file.seekg(0x0);
	for(uint8_t i = 0; i < rombanks; i++){
		m_mmu->init_rombank(i, file);
	}
	file.close();
}

Cartridge::~Cartridge(){}

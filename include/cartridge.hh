#ifndef CARTRIDGE_H
#define CARTRIDGE_H

class Cartridge;

#include "memory.hh"
#include <string>

class Cartridge : public Memory{
public:
	Cartridge();
	Cartridge(const std::string& fname);
	void Init(const std::string& fname);
	~Cartridge();

	void load(const std::string& fname);
	uint8_t read_byte(uint16_t addr);
	void write_byte(uint16_t addr, uint8_t val);
private:
	uint8_t rombank_0[0x4000];
	uint8_t rombank_1[0x4000];
	uint8_t ram_external[0x2000];
};

#endif

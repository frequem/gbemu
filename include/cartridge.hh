#ifndef CARTRIDGE_H
#define CARTRIDGE_H

class Cartridge;

#include "mmu.hh"
#include <string>
#include <cstdint>

class Cartridge{
public:
	Cartridge();
	Cartridge(const std::string& fname);
	void Init(const std::string& fname);
	void InitInternal(MMU *mmu);
	~Cartridge();

	void load(const std::string& fname);
private:
	std::string m_fname;
	MMU *m_mmu;
};

#endif

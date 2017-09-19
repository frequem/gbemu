#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <string>

#include "def.hh"
#include "mmu.hh"

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

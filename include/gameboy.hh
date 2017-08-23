#ifndef GAMEBOY_H
#define GAMEBOY_H

class Gameboy;

#include "cartridge.hh"
#include "mmu.hh"
#include "cpu.hh"

class Gameboy{
public:
	Gameboy();
	Gameboy(Cartridge *cartridge, Screen *screen, Joypad *joypad);
	void Init(Cartridge *cartridge, Screen *screen, Joypad *joypad);
	~Gameboy();

	void tick();
private:
	MMU *m_mmu;
	GPU *m_gpu;
	CPU *m_cpu;
};

#endif

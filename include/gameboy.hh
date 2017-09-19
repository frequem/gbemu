#ifndef GAMEBOY_H
#define GAMEBOY_H

#include "def.hh"
#include "cartridge.hh"
#include "screen.hh"
#include "joypad.hh"
#include "timer.hh"
#include "mmu.hh"
#include "gpu.hh"
#include "cpu.hh"

class Gameboy{
public:
	Gameboy();
	Gameboy(Cartridge *cartridge, Screen *screen, Joypad *joypad, uint8_t mode = MODE_DMG);
	void Init(Cartridge *cartridge, Screen *screen, Joypad *joypad, uint8_t mode = MODE_DMG);
	~Gameboy();

	void run();
private:
	uint8_t m_mode;
	
	Screen *m_screen;
	Joypad *m_joypad;
	Timer *m_timer;
	MMU *m_mmu;
	GPU *m_gpu;
	CPU *m_cpu;
};

#endif

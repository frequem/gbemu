#ifndef GAMEBOY_H
#define GAMEBOY_H

class Gameboy;

#include "cartridge.hh"
#include "mmu.hh"
#include "cpu.hh"
#include "gpu.hh"
#include "timer.hh"
#include "joypad.hh"
#include "screen.hh"

const uint8_t FPS = 60;
const uint32_t FRAMECYCLES = CLOCK_SPEED / FPS;

class Gameboy{
public:
	Gameboy();
	Gameboy(Cartridge *cartridge, Screen *screen, Joypad *joypad);
	void Init(Cartridge *cartridge, Screen *screen, Joypad *joypad);
	~Gameboy();

	void run();
private:
	Screen *m_screen;
	Joypad *m_joypad;
	Timer *m_timer;
	MMU *m_mmu;
	GPU *m_gpu;
	CPU *m_cpu;
};

#endif

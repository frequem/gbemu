#include "gameboy.hh"

Gameboy::Gameboy(){}

Gameboy::Gameboy(Cartridge *cartridge, Screen *screen, Joypad *joypad){
	Init(cartridge, screen, joypad);
}

void Gameboy::Init(Cartridge *cartridge, Screen *screen, Joypad *joypad){
	m_mmu = new MMU();
	m_gpu = new GPU(m_mmu, screen);
	m_cpu = new CPU(m_mmu);
	m_mmu->Init(cartridge, m_gpu, joypad);
}

void Gameboy::tick(){
	m_cpu->tick();
	m_gpu->tick();
}

Gameboy::~Gameboy(){
	if(m_mmu) delete m_mmu;
	if(m_gpu) delete m_gpu;
	if(m_cpu) delete m_cpu;
}

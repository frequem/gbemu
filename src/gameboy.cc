#include "gameboy.hh"

Gameboy::Gameboy(){}

Gameboy::Gameboy(Cartridge *cartridge, Screen *screen, Joypad *joypad){
	Init(cartridge, screen, joypad);
}

void Gameboy::Init(Cartridge *cartridge, Screen *screen, Joypad *joypad){
	m_screen = screen;
	m_timer = new Timer();
	m_mmu = new MMU();
	m_gpu = new GPU(m_mmu, screen, m_timer);
	m_cpu = new CPU(m_mmu, m_timer);
	m_mmu->Init(cartridge, m_gpu, joypad);
}

void Gameboy::run(){
	while(m_screen->enabled()){
		m_cpu->cycle();
		m_gpu->cycle();
		m_timer->cycle();
	}
}

Gameboy::~Gameboy(){
	if(m_timer) delete m_timer;
	if(m_mmu) delete m_mmu;
	if(m_gpu) delete m_gpu;
	if(m_cpu) delete m_cpu;
}

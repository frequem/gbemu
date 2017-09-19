#include "gameboy.hh"

Gameboy::Gameboy(){}

Gameboy::Gameboy(Cartridge *cartridge, Screen *screen, Joypad *joypad){
	Init(cartridge, screen, joypad);
}

void Gameboy::Init(Cartridge *cartridge, Screen *screen, Joypad *joypad){
	m_screen = screen;
	m_joypad = joypad;
	m_mmu = new MMU();
	m_timer = new Timer(m_mmu);
	m_gpu = new GPU(m_mmu, m_screen, m_timer);
	m_cpu = new CPU(m_mmu, m_timer);
	
	cartridge->InitInternal(m_mmu);
	m_joypad->InitInternal(m_mmu);
}

void Gameboy::run(){
	uint64_t prev_cycles = 0;
	while(m_screen->enabled()){
		
		while(((m_timer->get() - prev_cycles) < FRAMECYCLES)){
			m_joypad->cycle();
			m_cpu->cycle();
			m_gpu->cycle();
			m_timer->cycle();
			
		}
		m_screen->draw();
		prev_cycles = m_timer->get();
	}
}

Gameboy::~Gameboy(){
	if(m_timer) delete m_timer;
	if(m_mmu) delete m_mmu;
	if(m_gpu) delete m_gpu;
	if(m_cpu) delete m_cpu;
}

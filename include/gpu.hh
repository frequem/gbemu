#ifndef GPU_H
#define GPU_H

#include "def.hh"
#include "mmu.hh"
#include "screen.hh"
#include "timer.hh"

class GPU{
public:
	GPU();
	GPU(MMU *mmu, Screen *screen, Timer *timer, uint8_t mode);
	void Init(MMU *mmu, Screen *screen, Timer *timer, uint8_t mode);
	~GPU();

	void reset();

	void cycle();
private:
	uint8_t m_mode;
	
	MMU *m_mmu;
	Screen *m_screen;
	Timer *m_timer;

	uint64_t m_gpu_cycles;

	void set_gpumode(uint8_t mode, bool set_interrupt);
	
	void render_scanline();
	
	void render_scanline_tiles();
	void render_scanline_sprites();

	uint8_t* get_color_cgb(uint8_t id, uint8_t palette_id, uint16_t addr_source);
	
	static uint16_t get_addr_tiledata(uint16_t addr, uint8_t id, uint8_t size);
	static uint8_t* get_color_dmg(uint8_t id, uint8_t palette);
	
	uint8_t screenbuffer[144][160][3];
};

#endif

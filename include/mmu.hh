#ifndef MMU_H
#define MMU_H

class MMU;

#include "memory.hh"
#include "cartridge.hh"
#include "gpu.hh"
#include "joypad.hh"

const uint8_t INTR_VBLANK = 0b00000001;
const uint8_t INTR_LCDC = 	0b00000010;
const uint8_t INTR_TIMER =	0b00000100;
const uint8_t INTR_SERIAL =	0b00001000;
const uint8_t INTR_JOYPAD = 0b00010000;

class MMU : public Memory{
public:
	MMU();
	MMU(Cartridge *cartridge, GPU *gpu, Joypad *joypad);
	void Init(Cartridge *cartridge, GPU *gpu, Joypad *joypad);
	~MMU();

	void reset();
	void set_interrupt_flag(uint8_t intr, bool val);
	bool get_interrupt_flag(uint8_t intr);

	uint8_t read_byte(uint16_t addr);
	void write_byte(uint16_t addr, uint8_t val);
	uint16_t read_word(uint16_t addr);
	void write_word(uint16_t addr, uint16_t val);
	
private:
	uint8_t read_io_register(uint16_t addr);
	void write_io_register(uint16_t addr, uint8_t val);

	void copy(uint16_t addr_source, uint16_t addr_dest, uint16_t length);
	
	Cartridge *m_cartridge;
	GPU *m_gpu;
	Joypad *m_joypad;

	uint8_t ram_work_0[0x1000];
	uint8_t ram_work_1[0x1000];
	uint8_t ram_high[0x7F];
	
	uint8_t interrupt_flag; //FF0F
	uint8_t interrupt_enable; //FFFF
	
};

#endif

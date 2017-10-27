#ifndef MMU_H
#define MMU_H

#include <istream>

#include "def.hh"

class MMU{
public:
	MMU(uint8_t mode);
	~MMU();

	void reset();

	void allocate_rombanks(uint8_t banks);
	void init_rombank(uint8_t bank, std::istream& stream);
	void allocate_rambanks(uint8_t banks);
	
	uint8_t* get_byte(uint16_t addr);
	
	uint8_t read_byte(uint16_t addr);
	void write_byte(uint16_t addr, uint8_t val);
	uint16_t read_word(uint16_t addr);
	void write_word(uint16_t addr, uint16_t val);
	bool read_bit(uint16_t addr, uint8_t bitmask);
	void write_bit(uint16_t addr, uint8_t bitmask, bool set);
	void increment(uint16_t addr);
	
private:
	void handle_banking(uint16_t addr, uint8_t val);
	void dma_transfer(uint16_t addr_source);

	uint8_t m_mode;
	uint8_t m_memory[0x8000];
	uint8_t *m_rombanks;
	uint8_t *m_rambanks;
};

#endif

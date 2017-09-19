#ifndef MMU_H
#define MMU_H

#include <istream>

#include "def.hh"

class MMU{
public:
	MMU(uint8_t mode);
	~MMU();

	void reset();

	void increment(uint16_t addr);
	
	void write_bit(uint16_t addr, uint8_t bitmask, bool set);
	bool read_bit(uint16_t addr, uint8_t bitmask);

	uint8_t read_byte(uint16_t addr);
	void write_byte(uint16_t addr, uint8_t val);
	
	uint16_t read_word(uint16_t addr);
	void write_word(uint16_t addr, uint16_t val);

	void write_stream(uint16_t addr_start, std::istream& stream, uint32_t length);
	
private:
	uint8_t m_mode;
	void dma_transfer(uint16_t addr_source);

	uint8_t m_memory[0x10000];
};

#endif

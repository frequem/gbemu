#ifndef MEMORY_H
#define MEMORY_H
#include <cstdint>

class Memory{
public:
	virtual uint8_t read_byte(uint16_t addr) = 0;
	virtual void write_byte(uint16_t addr, uint8_t val) = 0;
	virtual ~Memory(){}
};

#endif

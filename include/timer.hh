#ifndef TIMER_H
#define TIMER_H

#include "def.hh"
#include "mmu.hh"

class Timer{
public:
	Timer();
	Timer(MMU *mmu, uint8_t mode);
	void Init(MMU *mmu, uint8_t mode);
	
	void reset();

	void cycle();
	void add(uint64_t cycles);
	bool elapse(uint64_t& cycle_counter, uint64_t cycles);
	uint64_t get();
	
private:
	uint8_t m_mode;
	
	MMU *m_mmu;
	uint64_t m_cycles;

	uint64_t m_tima_cycles;
	uint64_t m_div_cycles;
};

#endif

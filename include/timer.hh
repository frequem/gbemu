#ifndef TIMER_H
#define TIMER_H

class Timer;

#include "mmu.hh"

const uint32_t CLOCK_SPEED = 4194304;

const uint8_t TAC_TIMER_ENABLE = 0b100;

const uint32_t CLOCK_FREQUENCIES[4] = {
	4096,
	262144,
	65536,
	16382
};

const uint32_t CLOCK_FREQUENCY_DIV = 16382;

class Timer{
public:
	Timer();
	Timer(MMU *mmu);
	void Init(MMU *mmu);
	
	void reset();

	void cycle();
	void add(uint64_t cycles);
	bool elapse(uint64_t& cycle_counter, uint64_t cycles);
	uint64_t get();
	
private:
	MMU *m_mmu;
	uint64_t m_cycles;

	uint64_t m_tima_cycles;
	uint64_t m_div_cycles;
};

#endif

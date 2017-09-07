#ifndef TIMER_H
#define TIMER_H

#include <cstdint>

class Timer{
public:
	Timer();
	void cycle();
	void add_cycles(uint32_t cycles);
	uint32_t get_delta();
	void elapse_cycles(uint32_t cycles);
	bool try_elapse_cycles(uint32_t cycles);
private:
	uint32_t m_cycle_goal;
	uint32_t m_cycles;
};

#endif

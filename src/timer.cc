#include "timer.hh"
#include <iostream>

Timer::Timer(){
	m_cycles = 0;
	m_cycle_goal = 0;
}

void Timer::add_cycles(uint32_t cycles){
	m_cycle_goal += cycles;
}

void Timer::elapse_cycles(uint32_t cycles){
	m_cycles += cycles;
}

bool Timer::try_elapse_cycles(uint32_t cycles){
	if(get_delta() >= cycles){
		elapse_cycles(cycles);
		return true;
	}
	return false;
}

uint32_t Timer::get_delta(){
	return m_cycle_goal - m_cycles;
}

void Timer::cycle(){
}


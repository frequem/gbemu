#include "timer.hh"

#define READ(addr) m_mmu->read_byte(addr)
#define WRITE(addr, val) m_mmu->write_byte(addr, val)

Timer::Timer(){
}

Timer::Timer(MMU *mmu){
	Init(mmu);
}

void Timer::Init(MMU *mmu){
	m_mmu = mmu;
	reset();
}

void Timer::reset(){
	m_cycles = 0;
	m_tima_cycles = 0;
	m_div_cycles = 0;
}

void Timer::add(uint64_t cycles){
	m_cycles += cycles;
}

bool Timer::elapse(uint64_t& cycle_counter, uint64_t cycles){
	if((m_cycles - cycle_counter) >= cycles){
		cycle_counter = m_cycles - ((m_cycles - cycle_counter) % cycles);
		return true;
	}
	return false;
}

void Timer::cycle(){
	uint64_t cycles = CLOCK_SPEED / CLOCK_FREQUENCY_DIV;
	if(elapse(m_div_cycles, cycles)){
		m_mmu->increment(ADDR_DIVIDER_REGISTER);
	}
	
	if(m_mmu->read_bit(ADDR_TIMER_CONTROL, TAC_TIMER_ENABLE)){
		cycles = CLOCK_SPEED / CLOCK_FREQUENCIES[READ(ADDR_TIMER_CONTROL) & 0b11];
		if(elapse(m_tima_cycles, cycles)){
			if(READ(ADDR_TIMER_COUNTER) == 0xFF){
				WRITE(ADDR_TIMER_COUNTER, m_mmu->read_byte(ADDR_TIMER_MODULO));
				m_mmu->write_bit(ADDR_INTERRUPT_FLAG, INTR_TIMER, 1);
			}else{
				m_mmu->increment(ADDR_TIMER_COUNTER);
			}
		}
	}
}

uint64_t Timer::get(){
	return m_cycles;
}

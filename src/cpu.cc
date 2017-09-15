#include "cpu.hh"
#include <iostream>

CPU::CPU(){
}

CPU::CPU(MMU *mmu, Timer *timer){
	Init(mmu, timer);
}

void CPU::Init(MMU *mmu, Timer* timer){
	m_mmu = mmu;
	m_timer = timer;
	reset();
}

void CPU::reset(){
	PC = 0x0100;

	AF = 0x01B0;//DMG
	BC = 0x0013;
	DE = 0x00D8;
	HL = 0x014D;
	SP = 0xFFFE;
	interrupt_master_enable = false;
	interrupt_master_pending = false;
	halted = false;
}

void CPU::cycle(){
	handle_interrupts();
	
	if(halted)
		m_timer->add(4);
	else {
		handle_opcode(get_byte());
	}
}

uint8_t CPU::get_byte(){
	uint8_t res = m_mmu->read_byte(PC.val++);
	return res;
}

uint16_t CPU::get_word(){
	uint16_t res = m_mmu->read_word(PC.val);
	PC.val += 2;
	return res;
}

void CPU::set_flag(uint8_t flag, bool val){
	AF.low ^= (-val ^ AF.low) & flag; 
}

bool CPU::get_flag(uint8_t flag){
	return (AF.low & flag) == flag;
}

void CPU::stack_push(uint16_t val){
	SP.val -= 2;
	m_mmu->write_word(SP.val, val);
}

uint16_t CPU::stack_pop(){
	uint16_t res =  m_mmu->read_word(SP.val);
	SP.val += 2;
	return res;
}

void CPU::handle_interrupts(){	
	if(interrupt_master_enable && interrupt_master_pending){
		interrupt_master_pending = false;
	}else if(interrupt_master_enable || interrupt_master_pending){
		interrupt_master_pending = false;

		uint8_t flags = m_mmu->read_byte(0xFF0F); // interrupt flags
		uint8_t ena = m_mmu->read_byte(0xFFFF); // interrupt enable
		uint8_t i = 1;
		
		while(flags){
			if(flags & ena & i){
				interrupt_master_enable = false;
				halted = false;

				m_mmu->write_bit(ADDR_INTERRUPT_FLAG, i, 0);
				stack_push(PC.val);
				
				switch(i){
					case INTR_VBLANK:
						PC.val = 0x40; break;
					case INTR_LCDC:
						PC.val = 0x48; break;
					case INTR_TIMER:
						PC.val = 0x50; break;
					case INTR_SERIAL:
						PC.val = 0x58; break;
					case INTR_JOYPAD:
						PC.val = 0x60; break;
				}
			}
			flags >>= 1;
			i <<= 1;
		}
	}
}

CPU::~CPU(){
}

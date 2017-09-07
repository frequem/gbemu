#include "cpu.hh"

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
	if(!halted) handle_opcode(get_byte());
	handle_interrupts();
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
	return (AF.low & flag) != 0;
}

void CPU::stack_push(uint16_t val){
	m_mmu->write_word(SP.val, val);
	SP.val -= 2;
}

uint16_t CPU::stack_pop(){
	SP.val += 2;
	uint16_t res =  m_mmu->read_word(SP.val);
	return res;
}

void CPU::handle_interrupts(){
	if(interrupt_master_enable && interrupt_master_pending){
		interrupt_master_pending = false;
	}else if(interrupt_master_enable || interrupt_master_pending){
		interrupt_master_pending = false;
		
		uint8_t i = m_mmu->read_byte(0xFFFF) & m_mmu->read_byte(0xFF0F); //i_ena & i_flag
		if(i & 0b00011111){
			halted = false;
			interrupt_master_enable = false;
			stack_push(PC.val);
			m_timer->add_cycles(12);
		}
		
		if(i & INTR_VBLANK){
			PC.val = 0x40;
		}else if(i & INTR_LCDC){
			PC.val = 0x48;
		}else if(i & INTR_TIMER){
			PC.val = 0x50;
		}else if(i & INTR_SERIAL){
			PC.val = 0x58;
		}else if(i & INTR_JOYPAD){
			PC.val = 0x60;
		}
	}
}

CPU::~CPU(){
}

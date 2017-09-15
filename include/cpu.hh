#ifndef CPU_H
#define CPU_H

class CPU;

#include "mmu.hh"
#include "timer.hh"

const uint8_t FLAG_ZERO =		0b10000000;
const uint8_t FLAG_SUBTRACT =	0b01000000;
const uint8_t FLAG_HALF_CARRY =	0b00100000;
const uint8_t FLAG_CARRY =		0b00010000;

const int OP_CYCLES[0x100] = {
	4,  12, 8,  8,  4,  4,  8,  4,  20, 8,  8,  8, 4,  4,  8, 4,
	4,  12, 8,  8,  4,  4,  8,  4,  12, 8,  8,  8, 4,  4,  8, 4,
	8,  12, 8,  8,  4,  4,  8,  4,  8,  8,  8,  8, 4,  4,  8, 4,
	8,  12, 8,  8,  12, 12, 12, 4,  8,  8,  8,  8, 4,  4,  8, 4,
	4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4, 4,  4,  8, 4,
	4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4, 4,  4,  8, 4,
	4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4, 4,  4,  8, 4,
	8,  8,  8,  8,  8,  8,  4,  8,  4,  4,  4,  4, 4,  4,  8, 4,
	4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4, 4,  4,  8, 4,
	4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4, 4,  4,  8, 4,
	4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4, 4,  4,  8, 4,
	4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4, 4,  4,  8, 4,
	8,  12, 12, 16, 12, 16, 8,  16, 8,  16, 12, 4, 12, 24, 8, 16,
	8,  12, 12, 0,  12, 16, 8,  16, 8,  16, 12, 0, 12, 0,  8, 16,
	12, 12, 8,  0,  0,  16, 8,  16, 16, 4,  16, 0, 0,  0,  8, 16,
	12, 12, 8,  4,  0,  16, 8,  16, 12, 8,  16, 4, 0,  0,  8, 16,
};

const int OP_CYCLES_CB[0x10] = {
	8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8
};

union RegPair{
	struct{
		uint8_t low;
		uint8_t high;
	};
	uint16_t val;

	RegPair& operator=(const uint16_t& v){
		val = v;
		return *this;
	}
};

class CPU{
public:
	CPU();
	CPU(MMU *mmu, Timer *timer);
	void Init(MMU *mmu, Timer *timer);
	~CPU();

	void reset();
	void cycle();
private:
	MMU *m_mmu;
	Timer *m_timer;
	
	RegPair AF, BC, DE, HL, SP, PC;
	
	bool interrupt_master_enable;
	bool interrupt_master_pending;

	bool halted;

	uint8_t get_byte();
	uint16_t get_word();
	
	void set_flag(uint8_t flag, bool val);
	bool get_flag(uint8_t flag);

	void stack_push(uint16_t val);
	uint16_t stack_pop();
	
	void handle_interrupts();
	
	void handle_opcode(uint8_t opcode);
	void handle_opcode_cb(uint8_t opcode);
	
	//processor instructions
	void op_nop();
	void op_ld(uint16_t& reg, uint16_t val);
	void op_ld(uint16_t addr, uint8_t val);
	void op_ld(uint8_t& reg, uint8_t val);
	void op_ld(uint8_t& reg, uint16_t addr);
	void op_ld_mem(uint16_t addr, uint16_t val);
	void op_inc(uint8_t& reg);
	void op_inc(uint16_t& reg);
	void op_inc_mem(uint16_t addr);
	void op_dec(uint8_t& reg);
	void op_dec(uint16_t& reg);
	void op_dec_mem(uint16_t addr);
	void op_rlc(uint8_t& reg);
	void op_rlc(uint16_t addr);
	void op_add(uint8_t& reg, uint8_t val);
	void op_add(uint8_t& reg, uint16_t addr);
	void op_add(uint16_t& reg, uint16_t val);
	void op_add(uint16_t& reg, int8_t val);
	void op_stop();
	void op_rrc(uint8_t& reg);
	void op_rrc(uint16_t addr);
	void op_rl(uint8_t& reg);
	void op_rl(uint16_t addr);
	void op_jr(int8_t addr, bool condition);
	void op_rr(uint8_t& reg);
	void op_rr(uint16_t addr);
	void op_ldi(uint16_t& addr, uint8_t val);
	void op_ldi(uint8_t& reg, uint16_t& addr);
	void op_daa(uint8_t& reg);
	void op_cpl(uint8_t& reg);
	void op_ldd(uint16_t& addr, uint8_t val);
	void op_ldd(uint8_t& reg, uint16_t& addr);
	void op_scf();
	void op_ccf();
	void op_halt();
	void op_and(uint8_t& reg, uint8_t val);
	void op_and(uint8_t& reg, uint16_t addr);
	void op_adc(uint8_t& reg, uint8_t val);
	void op_adc(uint8_t& reg, uint16_t addr);
	void op_sub(uint8_t& reg, uint8_t val);
	void op_sub(uint8_t& reg, uint16_t addr);
	void op_sbc(uint8_t& reg, uint8_t val);
	void op_sbc(uint8_t& reg, uint16_t addr);
	void op_xor(uint8_t& reg, uint8_t val);
	void op_xor(uint8_t& reg, uint16_t addr);
	void op_or(uint8_t& reg, uint8_t val);
	void op_or(uint8_t& reg, uint16_t addr);
	void op_cp(uint8_t& reg, uint8_t val);
	void op_cp(uint8_t& reg, uint16_t addr);
	void op_ret(bool condition);
	void op_pop(uint16_t& reg);
	void op_jp(uint16_t addr, bool condition);
	void op_call(uint16_t addr, bool condition);
	void op_push(uint16_t val);
	void op_rst(uint8_t addr);
	void op_reti();
	void op_ldh_to_mem(uint8_t addr, uint8_t val);
	void op_ldh_to_reg(uint8_t& reg, uint8_t addr);
	void op_di();
	void op_ldhl(uint16_t& reg, int8_t addr);
	void op_ei();

	void op_swap(uint8_t& reg);
	void op_swap(uint16_t addr);
	void op_sla(uint8_t& reg);
	void op_sla(uint16_t addr);
	void op_sra(uint8_t& reg);
	void op_sra(uint16_t addr);
	void op_srl(uint8_t& reg);
	void op_srl(uint16_t addr);
	void op_bit(uint8_t& reg, uint8_t bit);
	void op_bit(uint16_t addr, uint8_t bit);
	void op_set(uint8_t& reg, uint8_t bit);
	void op_set(uint16_t addr, uint8_t bit);
	void op_res(uint8_t& reg, uint8_t bit);
	void op_res(uint16_t addr, uint8_t bit);
};

#endif

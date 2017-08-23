#include "cpu.hh"

void CPU::op_nop(){}

void CPU::op_ld(uint16_t& reg, uint16_t val){
	reg = val;
}

void CPU::op_ld(uint16_t addr, uint8_t val){
	m_mmu->write_byte(addr, val);
}

void CPU::op_ld(uint8_t& reg, uint8_t val){
	reg = val;
}

void CPU::op_ld(uint8_t& reg, uint16_t addr){
	reg = m_mmu->read_byte(addr);
}

void CPU::op_ld_mem(uint16_t addr, uint16_t val){
	m_mmu->write_word(addr, val);
}

void CPU::op_inc(uint8_t& reg){
	reg++;
	
	set_flag(FLAG_ZERO, reg == 0);
	set_flag(FLAG_SUBTRACT, 0);
	set_flag(FLAG_HALF_CARRY, (reg & 0b1111) == 0);
}

void CPU::op_inc(uint16_t& reg){
	reg++;
}

void CPU::op_inc_mem(uint16_t addr){
	uint8_t val = m_mmu->read_byte(addr);
	op_inc(val);
	m_mmu->write_byte(addr, val);
}

void CPU::op_dec(uint8_t& reg){
	reg--;
	
	set_flag(FLAG_ZERO, reg == 0);
	set_flag(FLAG_SUBTRACT, 1);
	set_flag(FLAG_HALF_CARRY, (reg & 0b1111) == 0b1111);
}

void CPU::op_dec(uint16_t& reg){
	reg--;
}

void CPU::op_dec_mem(uint16_t addr){
	uint8_t val = m_mmu->read_byte(addr);
	op_dec(val);
	m_mmu->write_byte(addr, val);
}

void CPU::op_rlc(uint8_t& reg){
	bool c = reg >> 7;

	reg = (reg << 1) | c;

	set_flag(FLAG_ZERO, reg == 0);
	set_flag(FLAG_SUBTRACT, 0);
	set_flag(FLAG_HALF_CARRY, 0);
	set_flag(FLAG_CARRY, c);
}

void CPU::op_rlc(uint16_t addr){
	uint8_t val = m_mmu->read_byte(addr);
	op_rlc(val);
	m_mmu->write_byte(addr, val);
}

void CPU::op_add(uint8_t& reg, uint8_t val){
	uint8_t res = reg + val;

	set_flag(FLAG_SUBTRACT, 0);
	set_flag(FLAG_HALF_CARRY, (res & 0xF) < (reg & 0xF));
	set_flag(FLAG_CARRY, (res < reg) || (res < val));

	op_ld(reg, res);
}

void CPU::op_add(uint8_t& reg, uint16_t addr){
	op_add(reg, m_mmu->read_byte(addr));
}

void CPU::op_add(uint16_t& reg, uint16_t val){
	uint16_t res = reg + val;
	
	set_flag(FLAG_SUBTRACT, 0);
	set_flag(FLAG_HALF_CARRY, (res & 0x7FF) < (reg & 0x7FF));
	set_flag(FLAG_CARRY, (res < reg) || (res < val));

	op_ld(reg, res);	
}

void CPU::op_add(uint16_t& reg, int8_t val){
	uint16_t res = reg + val;
	
	set_flag(FLAG_ZERO, 0);
	set_flag(FLAG_SUBTRACT, 0);
	set_flag(FLAG_HALF_CARRY, (res & 0xF) < (reg & 0xF));
	set_flag(FLAG_CARRY, (res & 0xFF) < (reg & 0xFF));

	reg = res;
}

void CPU::op_stop(){} // TODO: implement STOP

void CPU::op_rrc(uint8_t& reg){
	bool c = reg & 1;

	reg = (reg >> 1) | (c << 7);

	set_flag(FLAG_ZERO, reg == 0);
	set_flag(FLAG_SUBTRACT, 0);
	set_flag(FLAG_HALF_CARRY, 0);
	set_flag(FLAG_CARRY, c);
}

void CPU::op_rrc(uint16_t addr){
	uint8_t val = m_mmu->read_byte(addr);
	op_rrc(val);
	m_mmu->write_byte(addr, val);
}

void CPU::op_rl(uint8_t& reg){
	bool c = reg >> 7;

	reg = (reg << 1) | get_flag(FLAG_CARRY);
	
	set_flag(FLAG_ZERO, reg == 0);
	set_flag(FLAG_SUBTRACT, 0);
	set_flag(FLAG_HALF_CARRY, 0);
	set_flag(FLAG_CARRY, c);
}

void CPU::op_rl(uint16_t addr){
	uint8_t val = m_mmu->read_byte(addr);
	op_rl(val);
	m_mmu->write_byte(addr, val);
}

void CPU::op_jr(int8_t addr, bool condition){
	if(!condition)
		return;

	PC.val += addr;
}

void CPU::op_rr(uint8_t& reg){
	bool c = reg & 1;

	reg = (reg >> 1) | (get_flag(FLAG_CARRY) << 7);
	
	set_flag(FLAG_ZERO, reg == 0);
	set_flag(FLAG_SUBTRACT, 0);
	set_flag(FLAG_HALF_CARRY, 0);
	set_flag(FLAG_CARRY, c);
}

void CPU::op_rr(uint16_t addr){
	uint8_t val = m_mmu->read_byte(addr);
	op_rr(val);
	m_mmu->write_byte(addr, val);
}

void CPU::op_ldi(uint16_t& addr, uint8_t val){
	op_ld(addr, val);
	op_inc(addr);
}

void CPU::op_ldi(uint8_t& reg, uint16_t& addr){
	op_ld(reg, addr);
	op_inc(addr);
}

void CPU::op_daa(uint8_t& reg){
	uint8_t res = reg;

	bool h = get_flag(FLAG_HALF_CARRY);
	bool c = get_flag(FLAG_CARRY);
	
	if(get_flag(FLAG_SUBTRACT)){
		if(h) res = (res - 0x06) & 0xFF;
		if(c) res -= 0x60;
	}else{
		if(h || ((res & 0xF) > 9)) res += 0x06;
		if(c || (res > 0x9F)) res += 0x60;
	}

	reg = res;

	set_flag(FLAG_ZERO, res == 0);
	set_flag(FLAG_HALF_CARRY, 0);
	if(res >= 0x100) set_flag(FLAG_CARRY, 1);
}

void CPU::op_cpl(uint8_t& reg){
	reg = ~reg;

	set_flag(FLAG_SUBTRACT, 1);
	set_flag(FLAG_HALF_CARRY, 1);
}

void CPU::op_ldd(uint16_t& addr,  uint8_t val){
	op_ld(addr, val);
	op_dec(addr);
}

void CPU::op_ldd(uint8_t& reg, uint16_t& addr){
	op_ld(reg, addr);
	op_dec(addr);
}

void CPU::op_scf(){
	set_flag(FLAG_SUBTRACT, 0);
	set_flag(FLAG_HALF_CARRY, 0);
	set_flag(FLAG_CARRY, 1);
}

void CPU::op_ccf(){
	set_flag(FLAG_SUBTRACT, 0);
	set_flag(FLAG_HALF_CARRY, 0);
	set_flag(FLAG_CARRY, !get_flag(FLAG_CARRY));
}

void CPU::op_halt(){
	halted = true;
}

void CPU::op_and(uint8_t& reg, uint8_t val){
	reg = reg & val;
	
	set_flag(FLAG_ZERO, reg == 0);
	set_flag(FLAG_SUBTRACT, 0);
	set_flag(FLAG_HALF_CARRY, 1);
	set_flag(FLAG_CARRY, 0);
}

void CPU::op_and(uint8_t& reg, uint16_t addr){
	op_and(reg, m_mmu->read_byte(addr));
}

void CPU::op_adc(uint8_t& reg, uint8_t val){
	op_add(reg, (uint8_t)(val + get_flag(FLAG_CARRY)));
}

void CPU::op_adc(uint8_t& reg, uint16_t addr){
	op_adc(reg, m_mmu->read_byte(addr));
}

void CPU::op_sub(uint8_t& reg, uint8_t val){
	set_flag(FLAG_CARRY, val > reg);
	set_flag(FLAG_HALF_CARRY, (val & 0xF) > (reg & 0xF));

	reg -= val;
	
	set_flag(FLAG_ZERO, reg == 0);
	set_flag(FLAG_SUBTRACT, 1);
}

void CPU::op_sub(uint8_t& reg, uint16_t addr){
	op_sub(reg, m_mmu->read_byte(addr));
}

void CPU::op_sbc(uint8_t& reg, uint8_t val){
	op_sub(reg, (uint8_t)(val + get_flag(FLAG_CARRY)));
}

void CPU::op_sbc(uint8_t& reg, uint16_t addr){
	op_sbc(reg, m_mmu->read_byte(addr));
}

void CPU::op_xor(uint8_t& reg, uint8_t val){
	reg ^= val;
	
	set_flag(FLAG_ZERO, reg == 0);
	set_flag(FLAG_SUBTRACT, 0);
	set_flag(FLAG_HALF_CARRY, 0);
	set_flag(FLAG_CARRY, 0);
}

void CPU::op_xor(uint8_t& reg, uint16_t addr){
	op_xor(reg, m_mmu->read_byte(addr));
}

void CPU::op_or(uint8_t& reg, uint8_t val){
	reg = reg | val;
	
	set_flag(FLAG_ZERO, reg == 0);
	set_flag(FLAG_SUBTRACT, 0);
	set_flag(FLAG_HALF_CARRY, 0);
	set_flag(FLAG_CARRY, 0);
}

void CPU::op_or(uint8_t& reg, uint16_t addr){
	op_or(reg, m_mmu->read_byte(addr));
}

void CPU::op_cp(uint8_t& reg, uint8_t val){
	uint8_t res = reg - val;

	set_flag(FLAG_ZERO, res == 0);
	set_flag(FLAG_SUBTRACT, 1);
	set_flag(FLAG_HALF_CARRY, (reg & 0xf) < (val & 0xf));
	set_flag(FLAG_CARRY, reg < val);
}

void CPU::op_cp(uint8_t& reg, uint16_t addr){
	op_cp(reg, m_mmu->read_byte(addr)); 
}

void CPU::op_ret(bool condition){
	if(condition) op_jp(stack_pop(), true);
}

void CPU::op_pop(uint16_t& reg){
	reg = stack_pop();
}

void CPU::op_jp(uint16_t addr, bool condition){
	if(condition) PC = addr;
}

void CPU::op_call(uint16_t addr, bool condition){
	if(condition){
		stack_push(PC.val);
		op_jp(addr, true);
	}
}

void CPU::op_push(uint16_t val){
	stack_push(val);
}

void CPU::op_rst(uint8_t addr){
	op_call((uint16_t)addr, true);
}

void CPU::op_reti(){
	op_jp(stack_pop(), true);
	op_ei();
}

void CPU::op_ldh_to_mem(uint8_t addr, uint8_t val){
	op_ld((uint16_t)(addr + 0xFF00), val);
}

void CPU::op_ldh_to_reg(uint8_t& reg, uint8_t addr){
	op_ld(reg, (uint16_t)(addr + 0xFF00));
}

void CPU::op_di(){
	if(interrupt_master_enable){
		interrupt_master_enable = false;
		interrupt_master_pending = true;
	}
}

void CPU::op_ldhl(uint16_t& reg, int8_t addr){
	uint16_t res = reg + addr;

	op_ld(HL.val, res);
	
	set_flag(FLAG_ZERO, 0);
	set_flag(FLAG_SUBTRACT, 0);
	set_flag(FLAG_HALF_CARRY, (res & 0xF) < (reg & 0xF));
	set_flag(FLAG_CARRY, (res & 0xFF) < (reg & 0xFF));
}

void CPU::op_ei(){
	if(!interrupt_master_enable){
		interrupt_master_enable = true;
		interrupt_master_pending = true;
	}
}

void CPU::op_swap(uint8_t& reg){
	reg = ((reg & 0xF) << 4) | ((reg & 0xF0) >> 4);

	set_flag(FLAG_ZERO, reg == 0);
	set_flag(FLAG_SUBTRACT, 0);
	set_flag(FLAG_HALF_CARRY, 0);
	set_flag(FLAG_CARRY, 0);
}

void CPU::op_swap(uint16_t addr){
	uint8_t val = m_mmu->read_byte(addr);
	op_swap(val);
	m_mmu->write_byte(addr, val);
}

void CPU::op_sla(uint8_t& reg){
	bool c = reg >> 7;

	reg = reg << 1;

	set_flag(FLAG_ZERO, reg == 0);
	set_flag(FLAG_SUBTRACT, 0);
	set_flag(FLAG_HALF_CARRY, 0);
	set_flag(FLAG_CARRY, c);
}

void CPU::op_sla(uint16_t addr){
	uint8_t val = m_mmu->read_byte(addr);
	op_sla(val);
	m_mmu->write_byte(addr, val);
}

void CPU::op_sra(uint8_t& reg){
	bool c = reg & 1;

	reg = (reg >> 1) | (reg & 0x80);

	set_flag(FLAG_ZERO, reg == 0);
	set_flag(FLAG_SUBTRACT, 0);
	set_flag(FLAG_HALF_CARRY, 0);
	set_flag(FLAG_CARRY, c);
}

void CPU::op_sra(uint16_t addr){
	uint8_t val = m_mmu->read_byte(addr);
	op_sra(val);
	m_mmu->write_byte(addr, val);
}

void CPU::op_srl(uint8_t& reg){
	bool c = reg & 1;

	reg = reg >> 1;

	set_flag(FLAG_ZERO, reg == 0);
	set_flag(FLAG_SUBTRACT, 0);
	set_flag(FLAG_HALF_CARRY, 0);
	set_flag(FLAG_CARRY, c);
}

void CPU::op_srl(uint16_t addr){
	uint8_t val = m_mmu->read_byte(addr);
	op_srl(val);
	m_mmu->write_byte(addr, val);
}

void CPU::op_bit(uint8_t& reg, uint8_t bit){	
	set_flag(FLAG_ZERO, (reg & bit) == 0);
	set_flag(FLAG_SUBTRACT, 0);
	set_flag(FLAG_HALF_CARRY, 1);
}

void CPU::op_bit(uint16_t addr, uint8_t bit){
	uint8_t val = m_mmu->read_byte(addr);
	op_bit(val, bit);
	m_mmu->write_byte(addr, val);
}

void CPU::op_set(uint8_t& reg, uint8_t bit){
	reg |= bit;
}

void CPU::op_set(uint16_t addr, uint8_t bit){
	uint8_t val = m_mmu->read_byte(addr);
	op_set(val, bit);
	m_mmu->write_byte(addr, val);
}

void CPU::op_res(uint8_t& reg, uint8_t bit){
	reg &= ~bit;
}

void CPU::op_res(uint16_t addr, uint8_t bit){
	uint8_t val = m_mmu->read_byte(addr);
	op_res(val, bit);
	m_mmu->write_byte(addr, val);
}


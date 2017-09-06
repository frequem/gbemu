#include "cpu.hh"
#include <iostream>

void CPU::handle_opcode(uint8_t opcode){
	switch(opcode){
		case 0x00: op_nop(); break;
		case 0x01: op_ld(BC.val, get_word()); break;
		case 0x02: op_ld(BC.val, AF.high); break;
		case 0x03: op_inc(BC.val); break;
		case 0x04: op_inc(BC.high); break;
		case 0x05: op_dec(BC.high); break;
		case 0x06: op_ld(BC.high, get_byte()); break;
		case 0x07: op_rlc(AF.high); break;
		case 0x08: op_ld_mem(get_word(), SP.val); break;
		case 0x09: op_add(HL.val, BC.val); break;
		case 0x10: op_stop(); break;
		case 0x0A: op_ld(AF.high, BC.val); break;
		case 0x0B: op_dec(BC.val); break;
		case 0x0C: op_inc(BC.low); break;
		case 0x0D: op_dec(BC.low); break;
		case 0x0E: op_ld(BC.low, get_byte()); break;
		case 0x0F: op_rrc(AF.high); break;
		case 0x11: op_ld(DE.val, get_word()); break;
		case 0x12: op_ld(DE.val, AF.high); break;
		case 0x13: op_inc(DE.val); break;
		case 0x14: op_inc(DE.high); break;
		case 0x15: op_dec(DE.high); break;
		case 0x16: op_ld(DE.high, get_byte()); break;
		case 0x17: op_rl(AF.high); break;
		case 0x18: op_jr(get_byte(), true); break;
		case 0x19: op_add(HL.val, DE.val); break;
		case 0x1A: op_ld(AF.high, DE.val); break;
		case 0x1B: op_dec(DE.val); break;
		case 0x1C: op_inc(DE.low); break;
		case 0x1D: op_dec(DE.low); break;
		case 0x1E: op_ld(DE.low, get_byte()); break;
		case 0x1F: op_rr(AF.high); break;
		case 0x20: op_jr(get_byte(), !get_flag(FLAG_ZERO)); break;
		case 0x21: op_ld(HL.val, get_word()); break;
		case 0x22: op_ldi(HL.val, AF.high); break;
		case 0x23: op_inc(HL.val); break;
		case 0x24: op_inc(HL.high); break;
		case 0x25: op_dec(HL.high); break;
		case 0x26: op_ld(HL.high, get_byte()); break;
		case 0x27: op_daa(AF.high); break;
		case 0x28: op_jr(get_byte(), get_flag(FLAG_ZERO)); break;
		case 0x29: op_add(HL.val, HL.val); break;
		case 0x2A: op_ldi(AF.high, HL.val); break;
		case 0x2B: op_dec(HL.val); break;
		case 0x2C: op_inc(HL.low); break;
		case 0x2D: op_dec(HL.low); break;
		case 0x2E: op_ld(HL.low, get_byte()); break;
		case 0x2F: op_cpl(AF.high); break;
		case 0x30: op_jr(get_byte(), !get_flag(FLAG_CARRY)); break;
		case 0x31: op_ld(SP.val, get_word()); break;
		case 0x32: op_ldd(HL.val, AF.high); break;
		case 0x33: op_inc(SP.val); break;
		case 0x34: op_inc_mem(HL.val); break;
		case 0x35: op_dec_mem(HL.val); break;
		case 0x36: op_ld(HL.val, get_byte()); break;
		case 0x37: op_scf(); break;
		case 0x38: op_jr(get_byte(), get_flag(FLAG_CARRY)); break;
		case 0x39: op_add(HL.val, SP.val); break;
		case 0x3A: op_ldd(AF.high, HL.val); break;
		case 0x3B: op_dec(SP.val); break;
		case 0x3C: op_inc(AF.high); break;
		case 0x3D: op_dec(AF.high); break;
		case 0x3E: op_ld(AF.high, get_byte()); break;
		case 0x3F: op_ccf(); break;
		case 0x40: op_ld(BC.high, BC.high); break;
		case 0x41: op_ld(BC.high, BC.low); break;
		case 0x42: op_ld(BC.high, DE.high); break;
		case 0x43: op_ld(BC.high, DE.low); break;
		case 0x44: op_ld(BC.high, HL.high); break;
		case 0x45: op_ld(BC.high, HL.low); break;
		case 0x46: op_ld(BC.high, HL.val); break;
		case 0x47: op_ld(BC.high, AF.high); break;
		case 0x48: op_ld(BC.low, BC.high); break;
		case 0x49: op_ld(BC.low, BC.low); break;
		case 0x4A: op_ld(BC.low, DE.high); break;
		case 0x4B: op_ld(BC.low, DE.low); break;
		case 0x4C: op_ld(BC.low, HL.high); break;
		case 0x4D: op_ld(BC.low, HL.low); break;
		case 0x4E: op_ld(BC.low, HL.val); break;
		case 0x4F: op_ld(BC.low, AF.high); break;
		case 0x50: op_ld(DE.high, BC.high); break;
		case 0x51: op_ld(DE.high, BC.low); break;
		case 0x52: op_ld(DE.high, DE.high); break;
		case 0x53: op_ld(DE.high, DE.low); break;
		case 0x54: op_ld(DE.high, HL.high); break;
		case 0x55: op_ld(DE.high, HL.low); break;
		case 0x56: op_ld(DE.high, HL.val); break;
		case 0x57: op_ld(DE.high, AF.high); break; 
		case 0x58: op_ld(DE.low, BC.high); break;
		case 0x59: op_ld(DE.low, BC.low); break;
		case 0x5A: op_ld(DE.low, DE.high); break;
		case 0x5B: op_ld(DE.low, DE.low); break;
		case 0x5C: op_ld(DE.low, HL.high); break;
		case 0x5D: op_ld(DE.low, HL.low); break;
		case 0x5E: op_ld(DE.low, HL.val); break;
		case 0x5F: op_ld(DE.low, AF.high); break; 
		case 0x60: op_ld(HL.high, BC.high); break;
		case 0x61: op_ld(HL.high, BC.low); break;
		case 0x62: op_ld(HL.high, DE.high); break;
		case 0x63: op_ld(HL.high, DE.low); break;
		case 0x64: op_ld(HL.high, HL.high); break;
		case 0x65: op_ld(HL.high, HL.low); break;
		case 0x66: op_ld(HL.high, HL.val); break;
		case 0x67: op_ld(HL.high, AF.high); break; 
		case 0x68: op_ld(HL.low, BC.high); break;
		case 0x69: op_ld(HL.low, BC.low); break;
		case 0x6A: op_ld(HL.low, DE.high); break;
		case 0x6B: op_ld(HL.low, DE.low); break;
		case 0x6C: op_ld(HL.low, HL.high); break;
		case 0x6D: op_ld(HL.low, HL.low); break;
		case 0x6E: op_ld(HL.low, HL.val); break;
		case 0x6F: op_ld(HL.low, AF.high); break;
		case 0x70: op_ld(HL.val, BC.high); break;
		case 0x71: op_ld(HL.val, BC.low); break;
		case 0x72: op_ld(HL.val, DE.high); break;
		case 0x73: op_ld(HL.val, DE.low); break;
		case 0x74: op_ld(HL.val, HL.high); break;
		case 0x75: op_ld(HL.val, HL.low); break;
		case 0x76: op_halt(); break;
		case 0x77: op_ld(HL.val, AF.high); break;
		case 0x78: op_ld(AF.high, BC.high); break;
		case 0x79: op_ld(AF.high, BC.low); break;
		case 0x7A: op_ld(AF.high, DE.high); break;
		case 0x7B: op_ld(AF.high, DE.low); break;
		case 0x7C: op_ld(AF.high, HL.high); break;
		case 0x7D: op_ld(AF.high, HL.low); break;
		case 0x7E: op_ld(AF.high, HL.val); break;
		case 0x7F: op_ld(AF.high, AF.high); break;
		case 0x80: op_and(AF.high, BC.high); break;
		case 0x81: op_and(AF.high, BC.low); break;
		case 0x82: op_and(AF.high, DE.high); break;
		case 0x83: op_and(AF.high, DE.low); break;
		case 0x84: op_and(AF.high, HL.high); break;
		case 0x85: op_and(AF.high, HL.low); break;
		case 0x86: op_and(AF.high, HL.val); break;
		case 0x87: op_and(AF.high, AF.high); break;
		case 0x88: op_adc(AF.high, BC.high); break;
		case 0x89: op_adc(AF.high, BC.low); break;
		case 0x8A: op_adc(AF.high, DE.high); break;
		case 0x8B: op_adc(AF.high, DE.low); break;
		case 0x8C: op_adc(AF.high, HL.high); break;
		case 0x8D: op_adc(AF.high, HL.low); break;
		case 0x8E: op_adc(AF.high, HL.val); break;
		case 0x8F: op_adc(AF.high, AF.high); break;
		case 0x90: op_sub(AF.high, BC.high); break;
		case 0x91: op_sub(AF.high, BC.low); break;
		case 0x92: op_sub(AF.high, DE.high); break;
		case 0x93: op_sub(AF.high, DE.low); break;
		case 0x94: op_sub(AF.high, HL.high); break;
		case 0x95: op_sub(AF.high, HL.low); break;
		case 0x96: op_sub(AF.high, HL.val); break;
		case 0x97: op_sub(AF.high, AF.high); break;
		case 0x98: op_sbc(AF.high, BC.high); break;
		case 0x99: op_sbc(AF.high, BC.low); break;
		case 0x9A: op_sbc(AF.high, DE.high); break;
		case 0x9B: op_sbc(AF.high, DE.low); break;
		case 0x9C: op_sbc(AF.high, HL.high); break;
		case 0x9D: op_sbc(AF.high, HL.low); break;
		case 0x9E: op_sbc(AF.high, HL.val); break;
		case 0x9F: op_sbc(AF.high, AF.high); break;
		case 0xA0: op_and(AF.high, BC.high); break;
		case 0xA1: op_and(AF.high, BC.low); break;
		case 0xA2: op_and(AF.high, DE.high); break;
		case 0xA3: op_and(AF.high, DE.low); break;
		case 0xA4: op_and(AF.high, HL.high); break;
		case 0xA5: op_and(AF.high, HL.low); break;
		case 0xA6: op_and(AF.high, HL.val); break;
		case 0xA7: op_and(AF.high, AF.high); break;
		case 0xA8: op_xor(AF.high, BC.high); break;
		case 0xA9: op_xor(AF.high, BC.low); break;
		case 0xAA: op_xor(AF.high, DE.high); break;
		case 0xAB: op_xor(AF.high, DE.low); break;
		case 0xAC: op_xor(AF.high, HL.high); break;
		case 0xAD: op_xor(AF.high, HL.low); break;
		case 0xAE: op_xor(AF.high, HL.val); break;
		case 0xAF: op_xor(AF.high, AF.high); break;
		case 0xB0: op_or(AF.high, BC.high); break;
		case 0xB1: op_or(AF.high, BC.low); break;
		case 0xB2: op_or(AF.high, DE.high); break;
		case 0xB3: op_or(AF.high, DE.low); break;
		case 0xB4: op_or(AF.high, HL.high); break;
		case 0xB5: op_or(AF.high, HL.low); break;
		case 0xB6: op_or(AF.high, HL.val); break;
		case 0xB7: op_or(AF.high, AF.high); break;
		case 0xB8: op_cp(AF.high, BC.high); break;
		case 0xB9: op_cp(AF.high, BC.low); break;
		case 0xBA: op_cp(AF.high, DE.high); break;
		case 0xBB: op_cp(AF.high, DE.low); break;
		case 0xBC: op_cp(AF.high, HL.high); break;
		case 0xBD: op_cp(AF.high, HL.low); break;
		case 0xBE: op_cp(AF.high, HL.val); break;
		case 0xBF: op_cp(AF.high, AF.high); break;
		case 0xC0: op_ret(!get_flag(FLAG_ZERO)); break;
		case 0xC1: op_pop(BC.val); break;
		case 0xC2: op_jp(get_word(), !get_flag(FLAG_ZERO)); break;
		case 0xC3: op_jp(get_word(), true); break;
		case 0xC4: op_call(get_word(), !get_flag(FLAG_ZERO)); break;
		case 0xC5: op_push(BC.val); break;
		case 0xC6: op_and(AF.high, get_byte()); break;
		case 0xC7: op_rst(0x00); break;
		case 0xC8: op_ret(get_flag(FLAG_ZERO)); break;
		case 0xC9: op_ret(true); break;
		case 0xCA: op_jp(get_word(), get_flag(FLAG_ZERO)); break;
		case 0xCB: handle_opcode_cb(get_byte()); break; //cb prefix
		case 0xCC: op_call(get_word(), get_flag(FLAG_ZERO)); break;
		case 0xCD: op_call(get_word(), true); break;
		case 0xCE: op_adc(AF.high, get_byte()); break;
		case 0xCF: op_rst(0x08); break;
		case 0xD0: op_ret(!get_flag(FLAG_CARRY)); break;
		case 0xD1: op_pop(DE.val); break;
		case 0xD2: op_jp(get_word(), !get_flag(FLAG_CARRY)); break;
		case 0xD4: op_call(get_word(), !get_flag(FLAG_CARRY)); break;
		case 0xD5: op_push(DE.val); break;
		case 0xD6: op_sub(AF.high, get_byte()); break;
		case 0xD7: op_rst(0x10); break;
		case 0xD8: op_ret(get_flag(FLAG_CARRY)); break;
		case 0xD9: op_reti(); break;
		case 0xDA: op_jp(get_word(), get_flag(FLAG_CARRY)); break;
		case 0xDC: op_call(get_word(), get_flag(FLAG_CARRY)); break;
		case 0xDF: op_rst(0x18); break;
		case 0xE0: op_ldh_to_mem(get_byte(), AF.high); break;
		case 0xE1: op_pop(HL.val); break;
		case 0xE2: op_ldh_to_mem(BC.low, AF.high); break; //opcode manual states this uses 2 bytes, i only need one ??
		case 0xE5: op_push(HL.val); break;
		case 0xE6: op_and(AF.high, get_byte()); break;
		case 0xE7: op_rst(0x20); break;
		case 0xE9: op_jp(HL.val, true); break;
		case 0xEA: op_ld(get_word(), AF.high); break;
		case 0xEE: op_xor(AF.high, get_byte()); break;
		case 0xEF: op_rst(0x28); break;
		case 0xF0: op_ldh_to_reg(AF.high, get_byte()); break;
		case 0xF1: op_pop(AF.val); break;
		case 0xF2: op_ldh_to_reg(AF.high, BC.low); break;
		case 0xF3: op_di(); break;
		case 0xF5: op_push(AF.val); break;
		case 0xF6: op_or(AF.high, get_byte()); break;
		case 0xF7: op_rst(0x30); break;
		case 0xF8: op_ldhl(SP.val, get_byte()); break;
		case 0xF9: op_ld(SP.val, HL.val); break;
		case 0xFA: op_ld(AF.high, get_word()); break;
		case 0xFB: op_ei(); break;
		case 0xFE: op_cp(AF.high, get_byte()); break;
		case 0xFF: op_rst(0x38); break;
	}
}

void CPU::handle_opcode_cb(uint8_t opcode){
	switch(opcode){
		case 0x00: op_rlc(BC.high); break;
		case 0x01: op_rlc(BC.low); break;
		case 0x02: op_rlc(DE.high); break;
		case 0x03: op_rlc(DE.low); break;
		case 0x04: op_rlc(HL.high); break;
		case 0x05: op_rlc(HL.low); break;
		case 0x06: op_rlc(HL.val); break;
		case 0x07: op_rlc(AF.high); break;
		case 0x08: op_rrc(BC.high); break;
		case 0x09: op_rrc(BC.low); break;
		case 0x0A: op_rrc(DE.high); break;
		case 0x0B: op_rrc(DE.low); break;
		case 0x0C: op_rrc(HL.high); break;
		case 0x0D: op_rrc(HL.low); break;
		case 0x0E: op_rrc(HL.val); break;
		case 0x0F: op_rrc(AF.high); break;
		case 0x10: op_rl(BC.high); break;
		case 0x11: op_rl(BC.low); break;
		case 0x12: op_rl(DE.high); break;
		case 0x13: op_rl(DE.low); break;
		case 0x14: op_rl(HL.high); break;
		case 0x15: op_rl(HL.low); break;
		case 0x16: op_rl(HL.val); break;
		case 0x17: op_rl(AF.high); break;
		case 0x18: op_rr(BC.high); break;
		case 0x19: op_rr(BC.low); break;
		case 0x1A: op_rr(DE.high); break;
		case 0x1B: op_rr(DE.low); break;
		case 0x1C: op_rr(HL.high); break;
		case 0x1D: op_rr(HL.low); break;
		case 0x1E: op_rr(HL.val); break;
		case 0x1F: op_rr(AF.high); break;
		case 0x20: op_sla(BC.high); break;
		case 0x21: op_sla(BC.low); break;
		case 0x22: op_sla(DE.high); break;
		case 0x23: op_sla(DE.low); break;
		case 0x24: op_sla(HL.high); break;
		case 0x25: op_sla(HL.low); break;
		case 0x26: op_sla(HL.val); break;
		case 0x27: op_sla(AF.high); break;
		case 0x28: op_sra(BC.high); break;
		case 0x29: op_sra(BC.low); break;
		case 0x2A: op_sra(DE.high); break;
		case 0x2B: op_sra(DE.low); break;
		case 0x2C: op_sra(HL.high); break;
		case 0x2D: op_sra(HL.low); break;
		case 0x2E: op_sra(HL.val); break;
		case 0x2F: op_sra(AF.high); break;
		case 0x30: op_swap(BC.high); break;
		case 0x31: op_swap(BC.low); break;
		case 0x32: op_swap(DE.high); break;
		case 0x33: op_swap(DE.low); break;
		case 0x34: op_swap(HL.high); break;
		case 0x35: op_swap(HL.low); break;
		case 0x36: op_swap(HL.val); break;
		case 0x37: op_swap(AF.high); break;
		case 0x38: op_srl(BC.high); break;
		case 0x39: op_srl(BC.low); break;
		case 0x3A: op_srl(DE.high); break;
		case 0x3B: op_srl(DE.low); break;
		case 0x3C: op_srl(HL.high); break;
		case 0x3D: op_srl(HL.low); break;
		case 0x3E: op_srl(HL.val); break;
		case 0x3F: op_srl(AF.high); break;
		case 0x40: op_bit(BC.high, 	1); break;
		case 0x41: op_bit(BC.low, 	1); break;
		case 0x42: op_bit(DE.high, 	1); break;
		case 0x43: op_bit(DE.low, 	1); break;
		case 0x44: op_bit(HL.high, 	1); break;
		case 0x45: op_bit(HL.low, 	1); break;
		case 0x46: op_bit(HL.val, 	1); break;
		case 0x47: op_bit(AF.high, 	1); break;
		case 0x48: op_bit(BC.high, 	1 << 1); break;
		case 0x49: op_bit(BC.low, 	1 << 1); break;
		case 0x4A: op_bit(DE.high, 	1 << 1); break;
		case 0x4B: op_bit(DE.low, 	1 << 1); break;
		case 0x4C: op_bit(HL.high, 	1 << 1); break;
		case 0x4D: op_bit(HL.low, 	1 << 1); break;
		case 0x4E: op_bit(HL.val, 	1 << 1); break;
		case 0x4F: op_bit(AF.high, 	1 << 1); break;
		case 0x50: op_bit(BC.high, 	1 << 2); break;
		case 0x51: op_bit(BC.low, 	1 << 2); break;
		case 0x52: op_bit(DE.high, 	1 << 2); break;
		case 0x53: op_bit(DE.low, 	1 << 2); break;
		case 0x54: op_bit(HL.high, 	1 << 2); break;
		case 0x55: op_bit(HL.low, 	1 << 2); break;
		case 0x56: op_bit(HL.val, 	1 << 2); break;
		case 0x57: op_bit(AF.high, 	1 << 2); break;
		case 0x58: op_bit(BC.high, 	1 << 3); break;
		case 0x59: op_bit(BC.low, 	1 << 3); break;
		case 0x5A: op_bit(DE.high, 	1 << 3); break;
		case 0x5B: op_bit(DE.low, 	1 << 3); break;
		case 0x5C: op_bit(HL.high, 	1 << 3); break;
		case 0x5D: op_bit(HL.low, 	1 << 3); break;
		case 0x5E: op_bit(HL.val, 	1 << 3); break;
		case 0x5F: op_bit(AF.high, 	1 << 3); break;
		case 0x60: op_bit(BC.high, 	1 << 4); break;
		case 0x61: op_bit(BC.low, 	1 << 4); break;
		case 0x62: op_bit(DE.high, 	1 << 4); break;
		case 0x63: op_bit(DE.low, 	1 << 4); break;
		case 0x64: op_bit(HL.high, 	1 << 4); break;
		case 0x65: op_bit(HL.low, 	1 << 4); break;
		case 0x66: op_bit(HL.val, 	1 << 4); break;
		case 0x67: op_bit(AF.high, 	1 << 4); break;
		case 0x68: op_bit(BC.high, 	1 << 5); break;
		case 0x69: op_bit(BC.low, 	1 << 5); break;
		case 0x6A: op_bit(DE.high, 	1 << 5); break;
		case 0x6B: op_bit(DE.low, 	1 << 5); break;
		case 0x6C: op_bit(HL.high, 	1 << 5); break;
		case 0x6D: op_bit(HL.low, 	1 << 5); break;
		case 0x6E: op_bit(HL.val, 	1 << 5); break;
		case 0x6F: op_bit(AF.high, 	1 << 5); break;
		case 0x70: op_bit(BC.high, 	1 << 6); break;
		case 0x71: op_bit(BC.low, 	1 << 6); break;
		case 0x72: op_bit(DE.high, 	1 << 6); break;
		case 0x73: op_bit(DE.low, 	1 << 6); break;
		case 0x74: op_bit(HL.high, 	1 << 6); break;
		case 0x75: op_bit(HL.low, 	1 << 6); break;
		case 0x76: op_bit(HL.val, 	1 << 6); break;
		case 0x77: op_bit(AF.high, 	1 << 6); break;
		case 0x78: op_bit(BC.high, 	1 << 7); break;
		case 0x79: op_bit(BC.low, 	1 << 7); break;
		case 0x7A: op_bit(DE.high, 	1 << 7); break;
		case 0x7B: op_bit(DE.low, 	1 << 7); break;
		case 0x7C: op_bit(HL.high, 	1 << 7); break;
		case 0x7D: op_bit(HL.low, 	1 << 7); break;
		case 0x7E: op_bit(HL.val, 	1 << 7); break;
		case 0x7F: op_bit(AF.high, 	1 << 7); break;
		case 0x80: op_res(BC.high, 	1); break;
		case 0x81: op_res(BC.low, 	1); break;
		case 0x82: op_res(DE.high, 	1); break;
		case 0x83: op_res(DE.low, 	1); break;
		case 0x84: op_res(HL.high, 	1); break;
		case 0x85: op_res(HL.low, 	1); break;
		case 0x86: op_res(HL.val, 	1); break;
		case 0x87: op_res(AF.high, 	1); break;
		case 0x88: op_res(BC.high, 	1 << 1); break;
		case 0x89: op_res(BC.low, 	1 << 1); break;
		case 0x8A: op_res(DE.high, 	1 << 1); break;
		case 0x8B: op_res(DE.low, 	1 << 1); break;
		case 0x8C: op_res(HL.high, 	1 << 1); break;
		case 0x8D: op_res(HL.low, 	1 << 1); break;
		case 0x8E: op_res(HL.val, 	1 << 1); break;
		case 0x8F: op_res(AF.high, 	1 << 1); break;
		case 0x90: op_res(BC.high, 	1 << 2); break;
		case 0x91: op_res(BC.low, 	1 << 2); break;
		case 0x92: op_res(DE.high, 	1 << 2); break;
		case 0x93: op_res(DE.low, 	1 << 2); break;
		case 0x94: op_res(HL.high, 	1 << 2); break;
		case 0x95: op_res(HL.low, 	1 << 2); break;
		case 0x96: op_res(HL.val, 	1 << 2); break;
		case 0x97: op_res(AF.high, 	1 << 2); break;
		case 0x98: op_res(BC.high, 	1 << 3); break;
		case 0x99: op_res(BC.low, 	1 << 3); break;
		case 0x9A: op_res(DE.high, 	1 << 3); break;
		case 0x9B: op_res(DE.low, 	1 << 3); break;
		case 0x9C: op_res(HL.high, 	1 << 3); break;
		case 0x9D: op_res(HL.low, 	1 << 3); break;
		case 0x9E: op_res(HL.val, 	1 << 3); break;
		case 0x9F: op_res(AF.high, 	1 << 3); break;
		case 0xA0: op_res(BC.high, 	1 << 4); break;
		case 0xA1: op_res(BC.low, 	1 << 4); break;
		case 0xA2: op_res(DE.high, 	1 << 4); break;
		case 0xA3: op_res(DE.low, 	1 << 4); break;
		case 0xA4: op_res(HL.high, 	1 << 4); break;
		case 0xA5: op_res(HL.low, 	1 << 4); break;
		case 0xA6: op_res(HL.val, 	1 << 4); break;
		case 0xA7: op_res(AF.high, 	1 << 4); break;
		case 0xA8: op_res(BC.high, 	1 << 5); break;
		case 0xA9: op_res(BC.low, 	1 << 5); break;
		case 0xAA: op_res(DE.high, 	1 << 5); break;
		case 0xAB: op_res(DE.low, 	1 << 5); break;
		case 0xAC: op_res(HL.high, 	1 << 5); break;
		case 0xAD: op_res(HL.low, 	1 << 5); break;
		case 0xAE: op_res(HL.val, 	1 << 5); break;
		case 0xAF: op_res(AF.high, 	1 << 5); break;
		case 0xB0: op_res(BC.high, 	1 << 6); break;
		case 0xB1: op_res(BC.low, 	1 << 6); break;
		case 0xB2: op_res(DE.high, 	1 << 6); break;
		case 0xB3: op_res(DE.low, 	1 << 6); break;
		case 0xB4: op_res(HL.high, 	1 << 6); break;
		case 0xB5: op_res(HL.low, 	1 << 6); break;
		case 0xB6: op_res(HL.val, 	1 << 6); break;
		case 0xB7: op_res(AF.high, 	1 << 6); break;
		case 0xB8: op_res(BC.high, 	1 << 7); break;
		case 0xB9: op_res(BC.low, 	1 << 7); break;
		case 0xBA: op_res(DE.high, 	1 << 7); break;
		case 0xBB: op_res(DE.low, 	1 << 7); break;
		case 0xBC: op_res(HL.high, 	1 << 7); break;
		case 0xBD: op_res(HL.low, 	1 << 7); break;
		case 0xBE: op_res(HL.val, 	1 << 7); break;
		case 0xBF: op_res(AF.high, 	1 << 7); break;
		case 0xC0: op_set(BC.high, 	1); break;
		case 0xC1: op_set(BC.low, 	1); break;
		case 0xC2: op_set(DE.high, 	1); break;
		case 0xC3: op_set(DE.low, 	1); break;
		case 0xC4: op_set(HL.high, 	1); break;
		case 0xC5: op_set(HL.low, 	1); break;
		case 0xC6: op_set(HL.val, 	1); break;
		case 0xC7: op_set(AF.high, 	1); break;
		case 0xC8: op_set(BC.high, 	1 << 1); break;
		case 0xC9: op_set(BC.low, 	1 << 1); break;
		case 0xCA: op_set(DE.high, 	1 << 1); break;
		case 0xCB: op_set(DE.low, 	1 << 1); break;
		case 0xCC: op_set(HL.high, 	1 << 1); break;
		case 0xCD: op_set(HL.low, 	1 << 1); break;
		case 0xCE: op_set(HL.val, 	1 << 1); break;
		case 0xCF: op_set(AF.high, 	1 << 1); break;
		case 0xD0: op_set(BC.high, 	1 << 2); break;
		case 0xD1: op_set(BC.low, 	1 << 2); break;
		case 0xD2: op_set(DE.high, 	1 << 2); break;
		case 0xD3: op_set(DE.low, 	1 << 2); break;
		case 0xD4: op_set(HL.high, 	1 << 2); break;
		case 0xD5: op_set(HL.low, 	1 << 2); break;
		case 0xD6: op_set(HL.val, 	1 << 2); break;
		case 0xD7: op_set(AF.high, 	1 << 2); break;
		case 0xD8: op_set(BC.high, 	1 << 3); break;
		case 0xD9: op_set(BC.low, 	1 << 3); break;
		case 0xDA: op_set(DE.high, 	1 << 3); break;
		case 0xDB: op_set(DE.low, 	1 << 3); break;
		case 0xDC: op_set(HL.high, 	1 << 3); break;
		case 0xDD: op_set(HL.low, 	1 << 3); break;
		case 0xDE: op_set(HL.val, 	1 << 3); break;
		case 0xDF: op_set(AF.high, 	1 << 3); break;
		case 0xE0: op_set(BC.high, 	1 << 4); break;
		case 0xE1: op_set(BC.low, 	1 << 4); break;
		case 0xE2: op_set(DE.high, 	1 << 4); break;
		case 0xE3: op_set(DE.low, 	1 << 4); break;
		case 0xE4: op_set(HL.high, 	1 << 4); break;
		case 0xE5: op_set(HL.low, 	1 << 4); break;
		case 0xE6: op_set(HL.val, 	1 << 4); break;
		case 0xE7: op_set(AF.high, 	1 << 4); break;
		case 0xE8: op_set(BC.high, 	1 << 5); break;
		case 0xE9: op_set(BC.low, 	1 << 5); break;
		case 0xEA: op_set(DE.high, 	1 << 5); break;
		case 0xEB: op_set(DE.low, 	1 << 5); break;
		case 0xEC: op_set(HL.high, 	1 << 5); break;
		case 0xED: op_set(HL.low, 	1 << 5); break;
		case 0xEE: op_set(HL.val, 	1 << 5); break;
		case 0xEF: op_set(AF.high, 	1 << 5); break;
		case 0xF0: op_set(BC.high, 	1 << 6); break;
		case 0xF1: op_set(BC.low, 	1 << 6); break;
		case 0xF2: op_set(DE.high, 	1 << 6); break;
		case 0xF3: op_set(DE.low, 	1 << 6); break;
		case 0xF4: op_set(HL.high, 	1 << 6); break;
		case 0xF5: op_set(HL.low, 	1 << 6); break;
		case 0xF6: op_set(HL.val, 	1 << 6); break;
		case 0xF7: op_set(AF.high, 	1 << 6); break;
		case 0xF8: op_set(BC.high, 	1 << 7); break;
		case 0xF9: op_set(BC.low, 	1 << 7); break;
		case 0xFA: op_set(DE.high, 	1 << 7); break;
		case 0xFB: op_set(DE.low, 	1 << 7); break;
		case 0xFC: op_set(HL.high, 	1 << 7); break;
		case 0xFD: op_set(HL.low, 	1 << 7); break;
		case 0xFE: op_set(HL.val, 	1 << 7); break;
		case 0xFF: op_set(AF.high, 	1 << 7); break;
	}
}

#ifndef TEST_CPU_OP_XOR
#define TEST_CPU_OP_XOR

TEST(CPU_Test, op_xor_8_8){
	cpu->set_flag(FLAG_SUBTRACT, 1);
	cpu->set_flag(FLAG_HALF_CARRY, 1);
	cpu->set_flag(FLAG_CARRY, 1);
	
	uint8_t test = 0b11110000;
	
	cpu->op_xor(test, (uint8_t)0b00111100);
	
	ASSERT_EQ(test, 0b11001100);
	ASSERT_EQ(cpu->get_flag(FLAG_SUBTRACT), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), 0);
}
TEST(CPU_Test, op_xor_8_8_zero){
	cpu->set_flag(FLAG_ZERO, 0);
	
	uint8_t test = 0b01010101;
	
	cpu->op_xor(test, (uint8_t)0b01010101);
	
	ASSERT_EQ(test, 0);
	ASSERT_EQ(cpu->get_flag(FLAG_ZERO), 1);
}

TEST(CPU_Test, op_xor_8_16){
	uint16_t test_addr = 0xC000;
	uint8_t test = 0b00111100;
	
	mmu->write_byte(test_addr, 0b11110000);
	cpu->op_xor(test, test_addr);
	
	ASSERT_EQ(test, 0b11001100);
}
#endif

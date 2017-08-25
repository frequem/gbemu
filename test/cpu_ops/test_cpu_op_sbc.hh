#ifndef TEST_CPU_OP_SBC
#define TEST_CPU_OP_SBC

TEST(CPU_Test, op_sbc_8_8_carry_1){
	cpu->set_flag(FLAG_CARRY, 1);
	
	uint8_t test = 3;
	
	cpu->op_sbc(test, (uint8_t)2);
	
	ASSERT_EQ(test, 0);
}

TEST(CPU_Test, op_sbc_8_8_carry_0){
	cpu->set_flag(FLAG_CARRY, 0);
	
	uint8_t test = 3;
	
	cpu->op_sbc(test, (uint8_t)2);
	
	ASSERT_EQ(test, 1);
}

TEST(CPU_Test, op_sbc_8_16){
	cpu->set_flag(FLAG_CARRY, 1);
	
	uint16_t test_addr = 0xC000;
	uint8_t test = 3;

	mmu->write_byte(test_addr, 2);
	cpu->op_sbc(test, test_addr);
	
	ASSERT_EQ(test, 0);
}

#endif

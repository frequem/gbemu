#ifndef TEST_CPU_OP_RR
#define TEST_CPU_OP_RR

TEST(CPU_Test, op_rr_8_carry_0){
	cpu->set_flag(FLAG_CARRY, 1);
	
	uint8_t test = 0b11111110;
	
	cpu->op_rr(test);
	
	ASSERT_EQ(test, 0b11111111);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), 0);
}

TEST(CPU_Test, op_rr_8_carry_1){
	cpu->set_flag(FLAG_CARRY, 0);
	
	uint8_t test = 0b11111101;
	
	cpu->op_rr(test);
	
	ASSERT_EQ(test, 0b01111110);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), 1);
}

TEST(CPU_Test, op_rr_8_zero){
	cpu->set_flag(FLAG_ZERO, 0);
	cpu->set_flag(FLAG_CARRY, 0);
	
	uint8_t test = 0;
	
	cpu->op_rr(test);
	
	ASSERT_EQ(test, 0);
	ASSERT_EQ(cpu->get_flag(FLAG_ZERO), 1);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), 0);
}

TEST(CPU_Test, op_rr_16){
	cpu->set_flag(FLAG_CARRY, 1);
	
	uint16_t test_addr = 0xC000;
	
	mmu->write_byte(test_addr, 0b11111110);
	cpu->op_rr(test_addr);
	
	ASSERT_EQ(mmu->read_byte(test_addr), 0b11111111);
}
#endif

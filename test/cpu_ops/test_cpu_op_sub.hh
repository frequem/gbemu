#ifndef TEST_CPU_OP_SUB
#define TEST_CPU_OP_SUB

TEST(CPU_Test, op_sub_8_8){
	cpu->set_flag(FLAG_SUBTRACT, 0);
	cpu->set_flag(FLAG_HALF_CARRY, 1);
	cpu->set_flag(FLAG_CARRY, 1);
	
	uint8_t test = 10;
	
	cpu->op_sub(test, (uint8_t)3);
	
	ASSERT_EQ(test, 7);
	ASSERT_EQ(cpu->get_flag(FLAG_SUBTRACT), 1);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), 0);
}

TEST(CPU_Test, op_sub_8_8_zero){
	cpu->set_flag(FLAG_ZERO, 0);
	
	uint8_t test = 10;
	
	cpu->op_sub(test, (uint8_t)10);
	
	ASSERT_EQ(test, 0);
	ASSERT_EQ(cpu->get_flag(FLAG_ZERO), 1);
}

TEST(CPU_Test, op_sub_8_8_half_carry){
	cpu->set_flag(FLAG_HALF_CARRY, 0);
	cpu->set_flag(FLAG_CARRY, 1);
	
	uint8_t test = 0x10;
	
	cpu->op_sub(test, (uint8_t)2);
	
	ASSERT_EQ(test, 0x0E);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 1);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), 0);
}

TEST(CPU_Test, op_sub_8_8_carry){
	cpu->set_flag(FLAG_HALF_CARRY, 0);
	cpu->set_flag(FLAG_CARRY, 0);
	
	uint8_t test = 0x01;
	
	cpu->op_sub(test, (uint8_t)3);
	
	ASSERT_EQ(test, 0xFE);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 1);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), 1);
}

TEST(CPU_Test, op_sub_8_16){
	uint8_t test = 0x10;
	uint16_t test_addr = 0xC000;
	
	mmu->write_byte(test_addr, 0xF);
	cpu->op_sub(test, test_addr);
	
	ASSERT_EQ(test, 0x01);
	
}
#endif

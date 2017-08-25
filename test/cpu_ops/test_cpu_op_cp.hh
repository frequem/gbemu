#ifndef TEST_CPU_OP_CP
#define TEST_CPU_OP_CP

TEST(CPU_Test, op_cp_8_8){
	cpu->set_flag(FLAG_SUBTRACT, 0);
	cpu->set_flag(FLAG_HALF_CARRY, 1);
	cpu->set_flag(FLAG_CARRY, 1);
	
	uint8_t test = 10;
	
	cpu->op_cp(test, (uint8_t)3);
	
	ASSERT_EQ(test, 10);
	ASSERT_EQ(cpu->get_flag(FLAG_SUBTRACT), 1);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), 0);
}

TEST(CPU_Test, op_cp_8_8_zero){
	cpu->set_flag(FLAG_ZERO, 0);
	
	uint8_t test = 10;
	
	cpu->op_cp(test, (uint8_t)10);
	
	ASSERT_EQ(test, 10);
	ASSERT_EQ(cpu->get_flag(FLAG_ZERO), 1);
}

TEST(CPU_Test, op_cp_8_8_half_carry){
	cpu->set_flag(FLAG_HALF_CARRY, 0);
	cpu->set_flag(FLAG_CARRY, 1);
	
	uint8_t test = 0x10;
	
	cpu->op_cp(test, (uint8_t)2);
	
	ASSERT_EQ(test, 0x10);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 1);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), 0);
}

TEST(CPU_Test, op_cp_8_8_carry){
	cpu->set_flag(FLAG_HALF_CARRY, 0);
	cpu->set_flag(FLAG_CARRY, 0);
	
	uint8_t test = 0x01;
	
	cpu->op_cp(test, (uint8_t)3);
	
	ASSERT_EQ(test, 0x01);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 1);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), 1);
}

TEST(CPU_Test, op_cp_8_16){
	cpu->set_flag(FLAG_HALF_CARRY, 0);
	cpu->set_flag(FLAG_CARRY, 0);
	
	uint8_t test = 0x01;
	uint16_t test_addr = 0xC000;
	
	mmu->write_byte(test_addr, 3);
	cpu->op_cp(test, test_addr);
	
	ASSERT_EQ(test, 0x01);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 1);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), 1);
}
#endif

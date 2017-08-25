#ifndef TEST_CPU_OP_INC
#define TEST_CPU_OP_INC

TEST(CPU_Test, op_inc_8){
	cpu->set_flag(FLAG_ZERO, 1);
	cpu->set_flag(FLAG_SUBTRACT, 1);
	cpu->set_flag(FLAG_HALF_CARRY, 1);

	uint8_t test = 0x0E;
	
	cpu->op_inc(test);
	
	ASSERT_EQ(test, 0xF);
	ASSERT_EQ(cpu->get_flag(FLAG_ZERO), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_SUBTRACT), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 0);
	
}

TEST(CPU_Test, op_inc_8_half_carry){
	cpu->set_flag(FLAG_ZERO, 1);
	cpu->set_flag(FLAG_SUBTRACT, 1);
	cpu->set_flag(FLAG_HALF_CARRY, 0);
	
	uint8_t test = 0x0F;
	
	cpu->op_inc(test);
	
	ASSERT_EQ(test, 0x10);
	ASSERT_EQ(cpu->get_flag(FLAG_ZERO), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_SUBTRACT), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 1);
}

TEST(CPU_Test, op_inc_8_zero){
	cpu->set_flag(FLAG_ZERO, 0);
	cpu->set_flag(FLAG_SUBTRACT, 1);
	cpu->set_flag(FLAG_HALF_CARRY, 0);
	
	uint8_t test = 0xFF;

	cpu->op_inc(test);
	
	ASSERT_EQ(test, 0x00);
	ASSERT_EQ(cpu->get_flag(FLAG_ZERO), 1);
	ASSERT_EQ(cpu->get_flag(FLAG_SUBTRACT), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 1);
}

TEST(CPU_Test, op_inc_16){
	uint16_t test = 0xFFFF;
	
	cpu->op_inc(test);
	
	ASSERT_EQ(test, 0x0000);
}

TEST(CPU_Test, op_inc_mem){
	uint16_t test_addr = 0xC000;
	
	mmu->write_byte(test_addr, 0x01);
	cpu->op_inc_mem(test_addr);
	
	ASSERT_EQ(mmu->read_byte(test_addr), 0x02);
}
#endif

#ifndef TEST_CPU_OP_INC
#define TEST_CPU_OP_INC

TEST(CPU_Test, op_inc_8){
	uint8_t test = 0x0E;
	bool c = cpu->get_flag(FLAG_CARRY);
	
	cpu->op_inc(test);
	ASSERT_EQ(test, 0xF);
	ASSERT_EQ(cpu->get_flag(FLAG_ZERO), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_SUBTRACT), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), c);
	
}

TEST(CPU_Test, op_inc_8_half_carry){
	uint8_t test = 0x0F;
	bool c = cpu->get_flag(FLAG_CARRY);
	
	cpu->op_inc(test);
	ASSERT_EQ(test, 0x10);
	ASSERT_EQ(cpu->get_flag(FLAG_ZERO), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_SUBTRACT), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 1);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), c);
}

TEST(CPU_Test, op_inc_8_zero){
	uint8_t test = 0xFF;
	bool c = cpu->get_flag(FLAG_CARRY);

	cpu->op_inc(test);
	ASSERT_EQ(test, 0x00);
	ASSERT_EQ(cpu->get_flag(FLAG_ZERO), 1);
	ASSERT_EQ(cpu->get_flag(FLAG_SUBTRACT), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 1);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), c);
}

TEST(CPU_Test, op_inc_16){
	uint16_t test = 0xFFFF;
	bool z = cpu->get_flag(FLAG_ZERO);
	bool n = cpu->get_flag(FLAG_SUBTRACT);
	bool h = cpu->get_flag(FLAG_HALF_CARRY);
	bool c = cpu->get_flag(FLAG_CARRY);
	
	cpu->op_inc(test);
	ASSERT_EQ(test, 0x0000);
	ASSERT_EQ(cpu->get_flag(FLAG_ZERO), z);
	ASSERT_EQ(cpu->get_flag(FLAG_SUBTRACT), n);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), h);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), c);
}

TEST(CPU_Test, op_inc_mem){
	uint16_t test_addr = 0xC000;
	mmu->write_byte(test_addr, 0x01);
	
	cpu->op_inc_mem(test_addr);
	ASSERT_EQ(mmu->read_byte(test_addr), 0x02);
}
#endif

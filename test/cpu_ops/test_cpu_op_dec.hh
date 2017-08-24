#ifndef TEST_CPU_OP_DEC
#define TEST_CPU_OP_DEC

TEST(CPU_Test, op_dec_8){
	uint8_t test = 0x0F;
	bool c = cpu->get_flag(FLAG_CARRY);
	
	cpu->op_dec(test);
	ASSERT_EQ(test, 0xE);
	ASSERT_EQ(cpu->get_flag(FLAG_ZERO), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_SUBTRACT), 1);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), c);
	
}

TEST(CPU_Test, op_dec_8_half_carry){
	uint8_t test = 0x10;
	bool c = cpu->get_flag(FLAG_CARRY);
	
	cpu->op_dec(test);
	ASSERT_EQ(test, 0x0F);
	ASSERT_EQ(cpu->get_flag(FLAG_ZERO), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_SUBTRACT), 1);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 1);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), c);
}

TEST(CPU_Test, op_dec_8_zero){
	uint8_t test = 0x01;
	bool c = cpu->get_flag(FLAG_CARRY);

	cpu->op_dec(test);
	ASSERT_EQ(test, 0x00);
	ASSERT_EQ(cpu->get_flag(FLAG_ZERO), 1);
	ASSERT_EQ(cpu->get_flag(FLAG_SUBTRACT), 1);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), c);
}

TEST(CPU_Test, op_dec_16){
	uint16_t test = 0x0000;
	bool z = cpu->get_flag(FLAG_ZERO);
	bool n = cpu->get_flag(FLAG_SUBTRACT);
	bool h = cpu->get_flag(FLAG_HALF_CARRY);
	bool c = cpu->get_flag(FLAG_CARRY);
	
	cpu->op_dec(test);
	ASSERT_EQ(test, 0xFFFF);
	ASSERT_EQ(cpu->get_flag(FLAG_ZERO), z);
	ASSERT_EQ(cpu->get_flag(FLAG_SUBTRACT), n);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), h);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), c);
}

TEST(CPU_Test, op_dec_mem){
	uint16_t test_addr = 0xC000;
	mmu->write_byte(test_addr, 0x01);
	
	cpu->op_dec_mem(test_addr);
	ASSERT_EQ(mmu->read_byte(test_addr), 0x00);
}
#endif

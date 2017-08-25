#ifndef TEST_CPU_OP_DAA
#define TEST_CPU_OP_DAA

TEST(CPU_Test, op_daa_nochange){
	cpu->set_flag(FLAG_HALF_CARRY, 0);
	cpu->set_flag(FLAG_CARRY, 0);

	uint8_t test = 0b10011001;
	cpu->op_daa(test);

	
	ASSERT_EQ(test, 0b10011001);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), 0);
}

TEST(CPU_Test, op_daa_low_nibble){
	cpu->set_flag(FLAG_SUBTRACT, 0);
	cpu->set_flag(FLAG_HALF_CARRY, 0);
	cpu->set_flag(FLAG_CARRY, 0);

	uint8_t test = 0xF;
	cpu->op_daa(test);

	
	ASSERT_EQ(test, 0x15);
}

TEST(CPU_Test, op_daa_high_nibble){
	cpu->set_flag(FLAG_SUBTRACT, 0);
	cpu->set_flag(FLAG_HALF_CARRY, 0);
	cpu->set_flag(FLAG_CARRY, 0);

	uint8_t test = 0xF0;
	cpu->op_daa(test);
	
	ASSERT_EQ(test, 0x50);
}

TEST(CPU_Test, op_daa_half_carry){
	cpu->set_flag(FLAG_SUBTRACT, 0);
	cpu->set_flag(FLAG_HALF_CARRY, 1);
	cpu->set_flag(FLAG_CARRY, 0);

	uint8_t test = 0x08;
	cpu->op_daa(test);

	
	ASSERT_EQ(test, 0x0E);
}

TEST(CPU_Test, op_daa_carry){
	cpu->set_flag(FLAG_SUBTRACT, 0);
	cpu->set_flag(FLAG_HALF_CARRY, 0);
	cpu->set_flag(FLAG_CARRY, 1);

	uint8_t test = 0x80;
	cpu->op_daa(test);
	
	ASSERT_EQ(test, 0xE0);
}

TEST(CPU_Test, op_daa_subtract){
	cpu->set_flag(FLAG_SUBTRACT, 1);
	cpu->set_flag(FLAG_HALF_CARRY, 1);
	cpu->set_flag(FLAG_CARRY, 1);

	uint8_t test = 0x66;
	cpu->op_daa(test);
	
	ASSERT_EQ(test, 0x00);
}

TEST(CPU_Test, op_daa_carry_flag){
	cpu->set_flag(FLAG_SUBTRACT, 0);
	cpu->set_flag(FLAG_HALF_CARRY, 0);
	cpu->set_flag(FLAG_CARRY, 0);

	uint8_t test = 0xFF;
	cpu->op_daa(test);
	
	ASSERT_EQ(test, 0x65);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), 1);
}

TEST(CPU_Test, op_daa_zero){
	cpu->set_flag(FLAG_SUBTRACT, 1);
	cpu->set_flag(FLAG_HALF_CARRY, 1);
	cpu->set_flag(FLAG_CARRY, 0);

	uint8_t test = 0x06;
	cpu->op_daa(test);
	
	ASSERT_EQ(test, 0x00);
	ASSERT_EQ(cpu->get_flag(FLAG_ZERO), 1);
}
#endif


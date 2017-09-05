#ifndef TEST_CPU_OP_BIT
#define TEST_CPU_OP_BIT

TEST(CPU_Test, op_bit_8_0){
	cpu->set_flag(FLAG_ZERO, 1);
	cpu->set_flag(FLAG_SUBTRACT, 1);
	cpu->set_flag(FLAG_HALF_CARRY, 0);
	
	uint8_t test = 0b01010101;
	
	cpu->op_bit(test, 1);
	
	ASSERT_EQ(cpu->get_flag(FLAG_ZERO), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_SUBTRACT), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 1);
}

TEST(CPU_Test, op_bit_8_1){
	cpu->set_flag(FLAG_ZERO, 0);
	
	uint8_t test = 0b01010101;
	
	cpu->op_bit(test, 1 << 1);
	
	ASSERT_EQ(cpu->get_flag(FLAG_ZERO), 1);
}

TEST(CPU_Test, op_bit_8_2){
	cpu->set_flag(FLAG_ZERO, 1);
	
	uint8_t test = 0b01010101;
	
	cpu->op_bit(test, 1 << 2);
	
	ASSERT_EQ(cpu->get_flag(FLAG_ZERO), 0);
}

TEST(CPU_Test, op_bit_8_3){
	cpu->set_flag(FLAG_ZERO, 0);
	
	uint8_t test = 0b01010101;
	
	cpu->op_bit(test, 1 << 3);
	
	ASSERT_EQ(cpu->get_flag(FLAG_ZERO), 1);
}

TEST(CPU_Test, op_bit_8_4){
	cpu->set_flag(FLAG_ZERO, 1);
	
	uint8_t test = 0b01010101;
	
	cpu->op_bit(test, 1 << 4);
	
	ASSERT_EQ(cpu->get_flag(FLAG_ZERO), 0);
}

TEST(CPU_Test, op_bit_8_5){
	cpu->set_flag(FLAG_ZERO, 0);
	
	uint8_t test = 0b01010101;
	
	cpu->op_bit(test, 1 << 5);
	
	ASSERT_EQ(cpu->get_flag(FLAG_ZERO), 1);
}

TEST(CPU_Test, op_bit_8_6){
	cpu->set_flag(FLAG_ZERO, 1);
	
	uint8_t test = 0b01010101;
	
	cpu->op_bit(test, 1 << 6);
	
	ASSERT_EQ(cpu->get_flag(FLAG_ZERO), 0);
}

TEST(CPU_Test, op_bit_8_7){
	cpu->set_flag(FLAG_ZERO, 0);
	
	uint8_t test = 0b01010101;
	
	cpu->op_bit(test, 1 << 7);
	
	ASSERT_EQ(cpu->get_flag(FLAG_ZERO), 1);
}

TEST(CPU_Test, op_bit_16){
	cpu->set_flag(FLAG_ZERO, 0);
	
	uint16_t test_addr = 0xC000;
	
	mmu->write_byte(test_addr, 0b01010101);
	
	cpu->op_bit(test_addr, 1 << 7);
	
	ASSERT_EQ(cpu->get_flag(FLAG_ZERO), 1);
}
#endif

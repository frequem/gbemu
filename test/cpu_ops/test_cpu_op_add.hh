#ifndef TEST_CPU_OP_ADD
#define TEST_CPU_OP_ADD

TEST(CPU_Test, op_add_8_8){
	cpu->set_flag(FLAG_SUBTRACT, 1);
	
	uint8_t test = 2;
	cpu->op_add(test, (uint8_t)5);
	ASSERT_EQ(test, 7);
	ASSERT_EQ(cpu->get_flag(FLAG_SUBTRACT), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), 0);
}

TEST(CPU_Test, op_add_8_8_half_carry){
	cpu->set_flag(FLAG_HALF_CARRY, 0);
	
	uint8_t test = 0x0E;
	cpu->op_add(test, (uint8_t)2);
	ASSERT_EQ(test, 0x10);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 1);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), 0);
}

TEST(CPU_Test, op_add_8_8_carry){
	cpu->set_flag(FLAG_HALF_CARRY, 0);
	cpu->set_flag(FLAG_CARRY, 0);
	
	uint8_t test = 0xFE;
	cpu->op_add(test, (uint8_t)3);
	ASSERT_EQ(test, 0x01);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 1);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), 1);
}

TEST(CPU_Test, op_add_8_16){
	uint8_t test = 0xF0;
	uint16_t test_addr = 0xC000;
	mmu->write_byte(test_addr, 0xF);

	cpu->op_add(test, test_addr);
	ASSERT_EQ(test, 0xFF);
	
}

TEST(CPU_Test, op_add_16_16){
	cpu->set_flag(FLAG_SUBTRACT, 1);
	cpu->set_flag(FLAG_HALF_CARRY, 1);
	cpu->set_flag(FLAG_CARRY, 1);
	
	uint16_t test = 0xF00F;
	cpu->op_add(test, (uint16_t)0x0FF0);
	ASSERT_EQ(test, 0xFFFF);
	ASSERT_EQ(cpu->get_flag(FLAG_SUBTRACT), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), 0);
}

TEST(CPU_Test, op_add_16_16_half_carry){
	cpu->set_flag(FLAG_CARRY, 1);
	cpu->set_flag(FLAG_HALF_CARRY, 0);
	
	uint16_t test = 0x07FE;
	cpu->op_add(test, (uint16_t)0xF002);
	ASSERT_EQ(test, 0xF800);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 1);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), 0);
}

TEST(CPU_Test, op_add_16_16_carry){
	cpu->set_flag(FLAG_CARRY, 0);
	cpu->set_flag(FLAG_HALF_CARRY, 0);
	
	uint16_t test = 0xFFFE;
	cpu->op_add(test, (uint16_t)0x0003);
	ASSERT_EQ(test, 0x0001);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 1);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), 1);
}

TEST(CPU_Test, op_add_16_8_pos){
	cpu->set_flag(FLAG_ZERO, 1);
	cpu->set_flag(FLAG_SUBTRACT, 1);
	cpu->set_flag(FLAG_HALF_CARRY, 1);
	cpu->set_flag(FLAG_CARRY, 1);

	uint16_t test = 3;

	cpu->op_add(test, (int8_t)3);

	ASSERT_EQ(test, 6);	
	ASSERT_EQ(cpu->get_flag(FLAG_ZERO), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_SUBTRACT), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), 0);
}

TEST(CPU_Test, op_add_16_8_neg){
	uint16_t test = 3;
	cpu->op_add(test, (int8_t)-3);
	ASSERT_EQ(test, 0);	
}

TEST(CPU_Test, op_add_16_8_half_carry){
	cpu->set_flag(FLAG_HALF_CARRY, 0);
	uint16_t test = 0xF;
	cpu->op_add(test, (int8_t)3);
	ASSERT_EQ(test, 0x12);	
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 1);
}

TEST(CPU_Test, op_add_16_8_carry){
	cpu->set_flag(FLAG_CARRY, 0);
	cpu->set_flag(FLAG_HALF_CARRY, 0);
	uint16_t test = 0xFE;
	cpu->op_add(test, (int8_t)3);
	ASSERT_EQ(test, 0x101);	
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 1);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), 1);
}
#endif

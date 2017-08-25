#ifndef TEST_CPU_OP_LDHL
#define TEST_CPU_OP_LDHL

TEST(CPU_Test, op_ldhl_pos){
	cpu->set_flag(FLAG_ZERO, 1);
	cpu->set_flag(FLAG_SUBTRACT, 1);
	cpu->set_flag(FLAG_HALF_CARRY, 1);
	cpu->set_flag(FLAG_CARRY, 1);
	
	uint16_t test = 2;
	cpu->HL.val = 0;

	cpu->op_ldhl(test, 1);

	ASSERT_EQ(cpu->HL.val, 3);
	ASSERT_EQ(cpu->get_flag(FLAG_ZERO), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_SUBTRACT), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), 0);
}

TEST(CPU_Test, op_ldhl_neg){
	uint16_t test = 2;
	cpu->HL.val = 0;

	cpu->op_ldhl(test, -1);

	ASSERT_EQ(cpu->HL.val, 1);
}

TEST(CPU_Test, op_ldhl_half_carry){
	cpu->set_flag(FLAG_HALF_CARRY, 0);
	cpu->set_flag(FLAG_CARRY, 1);
	
	uint16_t test = 0x0F;
	cpu->HL.val = 0;

	cpu->op_ldhl(test, 1);

	ASSERT_EQ(cpu->HL.val, 0x10);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 1);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), 0);
}

TEST(CPU_Test, op_ldhl_carry){
	cpu->set_flag(FLAG_HALF_CARRY, 0);
	cpu->set_flag(FLAG_CARRY, 0);
	
	uint16_t test = 0xFF;
	cpu->HL.val = 0;

	cpu->op_ldhl(test, 2);

	ASSERT_EQ(cpu->HL.val, 0x101);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 1);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), 1);
}
#endif

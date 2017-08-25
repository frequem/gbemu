#ifndef TEST_CPU_OP_CPL
#define TEST_CPU_OP_CPL

TEST(CPU_Test, op_cpl){
	cpu->set_flag(FLAG_SUBTRACT, 0);
	cpu->set_flag(FLAG_HALF_CARRY, 0);
	
	uint8_t test = 0x0F;
	
	cpu->op_cpl(test);
	
	ASSERT_EQ(test, 0xF0);
	ASSERT_EQ(cpu->get_flag(FLAG_SUBTRACT), 1);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 1);
}
#endif

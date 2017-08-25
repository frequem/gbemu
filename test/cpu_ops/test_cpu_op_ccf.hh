#ifndef TEST_CPU_OP_CCF
#define TEST_CPU_OP_CCF

TEST(CPU_Test, op_scf_carry_0){
	cpu->set_flag(FLAG_SUBTRACT, 1);
	cpu->set_flag(FLAG_HALF_CARRY, 1);
	cpu->set_flag(FLAG_CARRY, 1);
	
	cpu->op_ccf();
	
	ASSERT_EQ(cpu->get_flag(FLAG_SUBTRACT), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), 0);
}

TEST(CPU_Test, op_scf_carry_1){
	cpu->set_flag(FLAG_SUBTRACT, 1);
	cpu->set_flag(FLAG_HALF_CARRY, 1);
	cpu->set_flag(FLAG_CARRY, 0);
	
	cpu->op_ccf();
	
	ASSERT_EQ(cpu->get_flag(FLAG_SUBTRACT), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), 1);
}

#endif

#ifndef TEST_CPU_OP_SCF
#define TEST_CPU_OP_SCF

TEST(CPU_Test, op_scf){
	cpu->set_flag(FLAG_SUBTRACT, 1);
	cpu->set_flag(FLAG_HALF_CARRY, 1);
	cpu->set_flag(FLAG_CARRY, 0);
	
	cpu->op_scf();
	
	ASSERT_EQ(cpu->get_flag(FLAG_SUBTRACT), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_HALF_CARRY), 0);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), 1);
}

#endif

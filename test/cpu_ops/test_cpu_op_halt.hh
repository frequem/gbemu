#ifndef TEST_CPU_OP_HALT
#define TEST_CPU_OP_HALT

TEST(CPU_Test, op_halt){
	cpu->halted = false;
	
	cpu->op_halt();
	
	ASSERT_EQ(cpu->halted, true);
}

#endif

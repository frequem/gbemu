#ifndef TEST_CPU_OP_CALL
#define TEST_CPU_OP_CALL

TEST(CPU_Test, op_call){
	cpu->PC.val = 0xF1;
	
	cpu->op_call(0xFF, true);
	
	ASSERT_EQ(cpu->PC.val, 0xFF);
	ASSERT_EQ(cpu->stack_pop(), 0xF1);
}

TEST(CPU_Test, op_call_cond_false){
	cpu->PC.val = 0xF4;
	
	cpu->op_call(0xFF, false);
	
	ASSERT_EQ(cpu->PC.val, 0xF4);
}
#endif

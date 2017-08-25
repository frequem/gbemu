#ifndef TEST_CPU_OP_RET
#define TEST_CPU_OP_RET

TEST(CPU_Test, op_ret){
	cpu->PC.val = 0;
	
	cpu->stack_push(0xFF);
	cpu->op_ret(true);
	
	ASSERT_EQ(cpu->PC.val, 0xFF);
}

TEST(CPU_Test, op_ret_cond_false){
	cpu->PC.val = 0;
	
	cpu->stack_push(0xFF);
	cpu->op_ret(false);
	
	ASSERT_EQ(cpu->PC.val, 0);
}

#endif

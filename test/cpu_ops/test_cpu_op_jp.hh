#ifndef TEST_CPU_OP_JP
#define TEST_CPU_OP_JP

TEST(CPU_Test, op_jp){
	cpu->PC.val = 0;
	
	cpu->op_jp(0xFF, true);
	
	ASSERT_EQ(cpu->PC.val, 0xFF);
}

TEST(CPU_Test, op_jp_cond_false){
	cpu->PC.val = 0;
	
	cpu->op_jp(0xFF, false);
	
	ASSERT_EQ(cpu->PC.val, 0);
}

#endif

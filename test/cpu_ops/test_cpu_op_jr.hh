#ifndef TEST_CPU_OP_JR
#define TEST_CPU_OP_JR

TEST(CPU_Test, op_jr_pos){
	cpu->PC.val = 0;
	
	cpu->op_jr(3, true);
	
	ASSERT_EQ(cpu->PC.val, 3);
}

TEST(CPU_Test, op_jr_neg){
	cpu->PC.val = 3;
	
	cpu->op_jr(-3, true);
	
	ASSERT_EQ(cpu->PC.val, 0);
}

TEST(CPU_Test, op_jr_cond_false){
	cpu->PC.val = 3;
	
	cpu->op_jr(-3, false);
	
	ASSERT_EQ(cpu->PC.val, 3);
}

#endif

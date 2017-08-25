#ifndef TEST_CPU_OP_POP
#define TEST_CPU_OP_POP

TEST(CPU_Test, op_pop){
	uint16_t test = 0;
	
	cpu->stack_push(0xFF);
	cpu->op_pop(test);
	
	ASSERT_EQ(test, 0xFF);
}
#endif

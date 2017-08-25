#ifndef TEST_CPU_OP_PUSH
#define TEST_CPU_OP_PUSH

TEST(CPU_Test, op_push){
	uint16_t test = 0x45;
	
	cpu->op_push(test);
	
	ASSERT_EQ(cpu->stack_pop(), 0x45);
}
#endif

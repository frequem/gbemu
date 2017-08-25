#ifndef TEST_CPU_OP_RST
#define TEST_CPU_OP_RST

TEST(CPU_Test, op_rst){
	cpu->PC.val = 0xF1;
	
	cpu->op_rst(0xFF);
	
	ASSERT_EQ(cpu->PC.val, 0xFF);
	ASSERT_EQ(cpu->stack_pop(), 0xF1);
}
#endif

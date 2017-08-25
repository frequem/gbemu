#ifndef TEST_CPU_OP_RETI
#define TEST_CPU_OP_RETI

TEST(CPU_Test, op_reti){
	cpu->interrupt_master_enable = false;
	cpu->interrupt_master_pending = false;
	cpu->PC.val = 0;
	
	cpu->stack_push(0xFF);
	cpu->op_reti();
	
	ASSERT_EQ(cpu->PC.val, 0xFF);
	ASSERT_EQ(cpu->interrupt_master_enable, true);
	ASSERT_EQ(cpu->interrupt_master_pending, true);
}
#endif

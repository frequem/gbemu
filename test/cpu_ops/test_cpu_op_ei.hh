#ifndef TEST_CPU_OP_EI
#define TEST_CPU_OP_EI

TEST(CPU_Test, op_ei){
	cpu->interrupt_master_enable = false;
	cpu->interrupt_master_pending = false;
	cpu->PC.val = 0xC000;

	mmu->write_byte(cpu->PC.val, 0);
	cpu->op_ei();
	
	ASSERT_EQ(cpu->interrupt_master_enable, true);
	ASSERT_EQ(cpu->interrupt_master_pending, true);

	cpu->cycle();
	
	ASSERT_EQ(cpu->interrupt_master_enable, true);
	ASSERT_EQ(cpu->interrupt_master_pending, false);
}
#endif

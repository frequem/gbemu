#ifndef TEST_CPU_OP_DI
#define TEST_CPU_OP_DI

TEST(CPU_Test, op_di){
	cpu->interrupt_master_enable = true;
	cpu->interrupt_master_pending = false;
	cpu->PC.val = 0xC000;

	mmu->write_byte(cpu->PC.val, 0);
	cpu->op_di();
	
	ASSERT_EQ(cpu->interrupt_master_enable, false);
	ASSERT_EQ(cpu->interrupt_master_pending, true);

	cpu->cycle();
	
	ASSERT_EQ(cpu->interrupt_master_enable, false);
	ASSERT_EQ(cpu->interrupt_master_pending, false);
}
#endif

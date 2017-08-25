#ifndef TEST_CPU_OP_LDH
#define TEST_CPU_OP_LDH

TEST(CPU_Test, op_ldh_to_mem){
	uint8_t test_addr = 0x0F; //interrupt flag
	
	cpu->op_ldh_to_mem(test_addr, 0xF1);
	
	ASSERT_EQ(mmu->read_byte(0xFF0F), 0xF1);	
}

TEST(CPU_Test, op_ldh_to_reg){
	uint8_t test = 0x00; //interrupt flag
	
	cpu->op_ldh_to_mem(0x0F, 77);
	cpu->op_ldh_to_reg(test, 0x0F);
	
	ASSERT_EQ(test, 77);	
}
#endif

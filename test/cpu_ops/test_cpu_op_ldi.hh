#ifndef TEST_CPU_OP_LDI
#define TEST_CPU_OP_LDI

TEST(CPU_Test, op_ldi_16_8){
	uint16_t test_addr = 0xC000; //ram_work_0[0]
	
	cpu->op_ldi(test_addr, (uint8_t)0xF);
	
	ASSERT_EQ(mmu->read_byte(test_addr-1), 0xF);
	ASSERT_EQ(test_addr, 0xC001);
}

TEST(CPU_Test, op_ldi_8_16){
	uint8_t test = 0;
	uint16_t test_addr = 0xC002;//ram_work_0[2]
	
	mmu->write_byte(test_addr, (uint8_t)0xF);
	cpu->op_ldi(test, test_addr);
	
	ASSERT_EQ(test, 0xF);
	ASSERT_EQ(test_addr, 0xC003);
}
#endif

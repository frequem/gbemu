#ifndef TEST_CPU_OP_LDD
#define TEST_CPU_OP_LDD

TEST(CPU_Test, op_ldd_16_8){
	uint16_t test_addr = 0xC001; //ram_work_0[0]
	
	cpu->op_ldd(test_addr, (uint8_t)0xF);
	
	ASSERT_EQ(mmu->read_byte(test_addr+1), 0xF);
	ASSERT_EQ(test_addr, 0xC000);
}

TEST(CPU_Test, op_ldd_8_16){
	uint8_t test = 0;
	uint16_t test_addr = 0xC002;//ram_work_0[2]
	
	mmu->write_byte(test_addr, (uint8_t)0xF);
	cpu->op_ldd(test, test_addr);
	
	ASSERT_EQ(test, 0xF);
	ASSERT_EQ(test_addr, 0xC001);
}
#endif

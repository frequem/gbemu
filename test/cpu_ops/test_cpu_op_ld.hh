#ifndef TEST_CPU_OP_LD
#define TEST_CPU_OP_LD

TEST(CPU_Test, op_ld_16_16){
	uint16_t test = 0;
	cpu->op_ld(test, (uint16_t)0xFF);
	ASSERT_EQ(test, 0xFF);	
}

TEST(CPU_Test, op_ld_16_8){
	uint16_t test_addr = 0xC000; //ram_work_0[0]
	cpu->op_ld(test_addr, (uint8_t)0xF);
	ASSERT_EQ(mmu->read_byte(test_addr), 0xF);
}

TEST(CPU_Test, op_ld_8_8){
	uint8_t test = 0;
	cpu->op_ld(test, (uint8_t)0xF);
	ASSERT_EQ(test, 0xF);
}

TEST(CPU_Test, op_ld_8_16){
	uint8_t test = 0;
	uint16_t test_addr = 0xC002;//ram_work_0[2]
	mmu->write_byte(test_addr, (uint8_t)0xF);
	cpu->op_ld(test, test_addr);
	ASSERT_EQ(test, 0xF);
}

TEST(CPU_Test, op_ld_mem_16_16){
	uint16_t test_addr = 0xC004; //ram_work_0[4]
	cpu->op_ld_mem(test_addr, (uint16_t)0xFF);
	ASSERT_EQ(mmu->read_word(test_addr), (uint16_t)0xFF);
}
#endif

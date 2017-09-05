#ifndef TEST_CPU_OP_SWAP
#define TEST_CPU_OP_SWAP

TEST(CPU_Test, op_swap_8){
	
	uint8_t test = 0b11000011;
	
	cpu->op_swap(test);
	
	ASSERT_EQ(test, 0b00111100);
}

TEST(CPU_Test, op_swap_8_zero){
	cpu->set_flag(FLAG_ZERO, 0);
	
	uint8_t test = 0;
	
	cpu->op_swap(test);
	
	ASSERT_EQ(test, 0);
	ASSERT_EQ(cpu->get_flag(FLAG_ZERO), 1);
}

TEST(CPU_Test, op_swap_16){
	uint16_t test_addr = 0xC000;
	
	mmu->write_byte(test_addr, 0b01011010);
	cpu->op_swap(test_addr);
	
	ASSERT_EQ(mmu->read_byte(test_addr), 0b10100101);
}
#endif

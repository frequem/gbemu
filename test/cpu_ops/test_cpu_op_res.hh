#ifndef TEST_CPU_OP_RES
#define TEST_CPU_OP_RES

TEST(CPU_Test, op_res_8_0){
	uint8_t test = 0b01010101;
	
	cpu->op_res(test, 1);
	
	ASSERT_EQ(test, 0b01010100);
}

TEST(CPU_Test, op_res_8_1){
	uint8_t test = 0b01010101;
	
	cpu->op_res(test, 1 << 1);
	
	ASSERT_EQ(test, 0b01010101);
}

TEST(CPU_Test, op_res_8_2){
	uint8_t test = 0b01010101;
	
	cpu->op_res(test, 1 << 2);
	
	ASSERT_EQ(test, 0b01010001);
}

TEST(CPU_Test, op_res_8_3){
	uint8_t test = 0b01010101;
	
	cpu->op_res(test, 1 << 3);
	
	ASSERT_EQ(test, 0b01010101);
}
TEST(CPU_Test, op_res_8_4){
	uint8_t test = 0b01010101;
	
	cpu->op_res(test, 1 << 4);
	
	ASSERT_EQ(test, 0b01000101);
}

TEST(CPU_Test, op_res_8_5){
	uint8_t test = 0b01010101;
	
	cpu->op_res(test, 1 << 5);
	
	ASSERT_EQ(test, 0b01010101);
}
TEST(CPU_Test, op_res_8_6){
	uint8_t test = 0b01010101;
	
	cpu->op_res(test, 1 << 6);
	
	ASSERT_EQ(test, 0b00010101);
}

TEST(CPU_Test, op_res_8_7){
	uint8_t test = 0b01010101;
	
	cpu->op_res(test, 1 << 7);
	
	ASSERT_EQ(test, 0b01010101);
}

TEST(CPU_Test, op_res_16){
	uint16_t test_addr = 0xC000;
	
	mmu->write_byte(test_addr, 0b01010101);
	
	cpu->op_res(test_addr, 1 << 6);
	
	ASSERT_EQ(mmu->read_byte(test_addr), 0b00010101);
}
#endif

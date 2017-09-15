#ifndef TEST_GPU
#define TEST_GPU

TEST(GPU_Test, get_addr_tiledata_8000){
	uint16_t addr = gpu->get_addr_tiledata(0x8000, 4, 16);
	ASSERT_EQ(addr, 0x8040);
}

TEST(GPU_Test, get_addr_tiledata_8800_zero){
	uint16_t addr = gpu->get_addr_tiledata(0x8800, 0, 16);
	ASSERT_EQ(addr, 0x9000);
}

TEST(GPU_Test, get_addr_tiledata_8800_pos){
	uint16_t addr = gpu->get_addr_tiledata(0x8800, 4, 16);
	ASSERT_EQ(addr, 0x9040);
}

TEST(GPU_Test, get_addr_tiledata_8800_neg){
	uint16_t addr = gpu->get_addr_tiledata(0x8800, 252, 16); //252 == -4
	ASSERT_EQ(addr, 0x8FC0);
}
#endif

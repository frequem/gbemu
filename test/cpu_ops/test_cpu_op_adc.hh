#ifndef TEST_CPU_OP_ADC
#define TEST_CPU_OP_ADC

TEST(CPU_Test, op_adc_8_8_carry_1){
	cpu->set_flag(FLAG_CARRY, 1);
	
	uint8_t test = 0;
	
	cpu->op_adc(test, (uint8_t)2);
	
	ASSERT_EQ(test, 3);
}

TEST(CPU_Test, op_adc_8_8_carry_0){
	cpu->set_flag(FLAG_CARRY, 0);
	
	uint8_t test = 0;
	
	cpu->op_adc(test, (uint8_t)2);
	
	ASSERT_EQ(test, 2);
}

TEST(CPU_Test, op_adc_8_16){
	cpu->set_flag(FLAG_CARRY, 1);
	
	uint16_t test_addr = 0xC000;
	uint8_t test = 0;

	mmu->write_byte(test_addr, 2);
	cpu->op_adc(test, test_addr);
	
	ASSERT_EQ(test, 3);
}

#endif

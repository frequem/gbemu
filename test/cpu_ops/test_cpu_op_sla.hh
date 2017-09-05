#ifndef TEST_CPU_OP_SLA
#define TEST_CPU_OP_SLA

TEST(CPU_Test, op_sla_8_carry_0){
	cpu->set_flag(FLAG_CARRY, 1);
	
	uint8_t test = 0b01111111;
	
	cpu->op_sla(test);
	
	ASSERT_EQ(test, 0b11111110);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), 0);
}

TEST(CPU_Test, op_sla_8_carry_1){
	cpu->set_flag(FLAG_CARRY, 0);
	
	uint8_t test = 0b11111111;
	
	cpu->op_sla(test);
	
	ASSERT_EQ(test, 0b11111110);
	ASSERT_EQ(cpu->get_flag(FLAG_CARRY), 1);
}

TEST(CPU_Test, op_sla_8_zero){
	cpu->set_flag(FLAG_ZERO, 0);
	
	uint8_t test = 0;
	
	cpu->op_sla(test);
	
	ASSERT_EQ(test, 0);
	ASSERT_EQ(cpu->get_flag(FLAG_ZERO), 1);
}

TEST(CPU_Test, op_sla_16){
	uint16_t test_addr = 0xC000;
	
	mmu->write_byte(test_addr, 0b01011010);
	cpu->op_sla(test_addr);
	
	ASSERT_EQ(mmu->read_byte(test_addr), 0b10110100);
}
#endif

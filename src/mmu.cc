#include "mmu.hh"
#include <iostream>

MMU::MMU(){}

MMU::MMU(Cartridge *cartridge, GPU *gpu, Joypad *joypad){
	Init(cartridge, gpu, joypad);
}

void MMU::Init(Cartridge *cartridge, GPU *gpu, Joypad *joypad){
	m_cartridge = cartridge;
	m_gpu = gpu;
	m_joypad = joypad;
	reset();
}

void MMU::reset(){
	interrupt_flag = 0;
	interrupt_enable = 0;

	
}

void MMU::set_interrupt_flag(uint8_t intr, bool val){
	interrupt_flag ^= (-val ^ interrupt_flag) & intr; 
}

bool MMU::get_interrupt_flag(uint8_t intr){
	return (interrupt_flag & intr) != 0;
}

uint8_t MMU::read_byte(uint16_t addr){
	if(addr < 0x8000){
		return m_cartridge->read_byte(addr);
	}else if(addr < 0xA000){//vram
		return m_gpu->read_byte(addr);
	}else if(addr < 0xC000){
		return m_cartridge->read_byte(addr);
	}else if(addr < 0xD000){
		return ram_work_0[addr & 0x0FFF];
	}else if(addr < 0xE000){
		return ram_work_1[addr & 0x0FFF];
	}else if(addr < 0xF000){ //echo ram (workram 0)
		return ram_work_0[addr & 0x0FFF];
	}else if(addr < 0xFE00){ //echo ram (half of workram 1)
		return ram_work_1[addr & 0x0FFF];
	}else if(addr < 0xFEA0){//oam
		return m_gpu->read_byte(addr);
	}else if(addr < 0xFF00){
		//not usable (gbdev.gg8.se/wiki/articles/Memory_Map)
		return 0;
	}else if(addr < 0xFF80){
		//i/o registers
		return read_io_register(addr);
	}else if(addr < 0xFFFF){
		return ram_high[addr & 0x7F];
	}else if(addr == 0xFFFF){
		return interrupt_enable;
	}
	return 0;
}

uint8_t MMU::read_io_register(uint16_t addr){
	switch(addr){
		case 0xFF00:
			return m_joypad->read_byte(addr);
		case 0xFF0F:
			return interrupt_flag;
		case 0xFF42:
		case 0xFF43:
		case 0xFF44:
		case 0xFF47:
		case 0xFF48:
		case 0xFF49:
		case 0xFF4A:
		case 0xFF4B:
			return m_gpu->read_byte(addr);
		case 0xFF26: break; //TODO: implement NR 52
		default:
			std::cout << "io read: " << std::hex << (int)addr << std::endl;
	}
	return 0;
}

void MMU::write_byte(uint16_t addr, uint8_t val){
	if(addr < 0x8000){
		m_cartridge->write_byte(addr, val);
	}else if(addr < 0xA000){//vram
		m_gpu->write_byte(addr, val);
	}else if(addr < 0xC000){//external ram
		m_cartridge->write_byte(addr, val);
	}else if(addr < 0xD000){
		ram_work_0[addr & 0x0FFF] = val;
	}else if(addr < 0xE000){
		ram_work_1[addr & 0x0FFF] = val;
	}else if(addr < 0xF000){ //echo ram (workram 0)
		ram_work_0[addr & 0x0FFF] = val;
	}else if(addr < 0xFE00){ //echo ram (half of workram 1)
		ram_work_1[addr & 0x0FFF] = val;
	}else if(addr < 0xFEA0){//oam
		m_gpu->write_byte(addr, val);
	}else if(addr < 0xFF00){
		//not usable (gbdev.gg8.se/wiki/articles/Memory_Map)
	}else if(addr < 0xFF80){
		write_io_register(addr, val);
	}else if(addr < 0xFFFF){
		ram_high[addr & 0x7F] = val;
	}else if(addr == 0xFFFF){
		interrupt_enable = val;
	}
}

void MMU::write_io_register(uint16_t addr, uint8_t val){
	switch(addr){
		case 0xFF00:
			m_joypad->write_byte(addr, val); break;
		case 0xFF0F:
			interrupt_flag = val; break;
		case 0xFF40:
		case 0xFF41:
		case 0xFF42:
		case 0xFF43:
		case 0xFF47:
		case 0xFF48:
		case 0xFF49:
		case 0xFF4A:
		case 0xFF4B:
			m_gpu->write_byte(addr, val); break;
		case 0xFF46: //transfer dma to oam
			copy(((uint16_t)val) << 8, 0xFE00, 140); break; //OAM is 160 bytes long but ff46 only transfers 140 for some reason
		case 0xFF7F: break; // there seems to be a bug in tetris world, where this io is written to, even though it has no use
		case 0xFF01: break; //TODO: implement serial transfer data
		case 0xFF02: break; //TODO: implement serial IO control
		case 0xFF06: break; //TODO: implement timer modulo
		//TODO: implement audio
		case 0xFF10: break;
		case 0xFF12: break;
		case 0xFF14: break;
		case 0xFF17: break;
		case 0xFF19: break;
		case 0xFF1A: break;
		case 0xFF21: break; 
		case 0xFF23: break;
		case 0xFF24: break;
		case 0xFF25: break;
		case 0xFF26: break; 
		default:
			std::cout << "io write: " << std::hex << (int)addr << ":" << std::hex << (int)val << std::endl;
	}
}

void MMU::copy(uint16_t addr_source, uint16_t addr_dest, uint16_t length){
	for(uint16_t i = 0; i < length; i++){
		write_byte(addr_dest + i, read_byte(addr_source + i));
	}
}

uint16_t MMU::read_word(uint16_t addr){
	return (read_byte(addr+1)<<8 | read_byte(addr));
}

void MMU::write_word(uint16_t addr, uint16_t val){
	write_byte(addr, val & 0xFF);
	write_byte(addr+1, val >> 8);
}

MMU::~MMU(){
}

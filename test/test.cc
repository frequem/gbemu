#include <gtest/gtest.h>

#define private public //awful hack, but i'm not changing my prod files
#include "mmu.hh"
#include "gpu.hh"
#include "cpu.hh"
#include "timer.hh"
#undef private

MMU *mmu;
GPU *gpu;
CPU *cpu;
Timer *timer;

#include "test_cpu_ops.hh"
#include "test_gpu.hh"

int main(int argc, char **argv){
	mmu = new MMU(0);
	timer = new Timer(mmu, 0);
	gpu = new GPU(mmu, NULL, timer, 0);
	cpu = new CPU(mmu, timer, 0);
	
	::testing::InitGoogleTest(&argc, argv);
	
	int res = RUN_ALL_TESTS();
	
	delete mmu;
	delete gpu;
	delete cpu;
	delete timer;
	
	return res;
}

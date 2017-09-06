#include <gtest/gtest.h>

#define private public //awful hack, but i'm not changing my prod files
#include "mmu.hh"
#include "gpu.hh"
#include "cpu.hh"
#undef private

MMU *mmu;
GPU *gpu;
CPU *cpu;

#include "test_cpu_ops.hh"
#include "test_gpu.hh"

int main(int argc, char **argv){
	mmu = new MMU();
	gpu = new GPU(mmu, NULL);
	cpu = new CPU(mmu);
	mmu->Init(NULL, gpu, NULL);
	
	::testing::InitGoogleTest(&argc, argv);
	
	int res = RUN_ALL_TESTS();
	
	delete mmu;
	delete gpu;
	delete cpu;
	
	return res;
}

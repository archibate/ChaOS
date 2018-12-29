#pragma once

#include <asm/mmu.h>
#include <mm/kbase.h>

#define mmu_set_pd(pd)	mmu_set_ppd(KV2P((ulong)(pd)))
#define mmu_get_pd()	((pde_t*)KP2V(mmu_get_ppd()))
#define mmu_flushall()	mmu_set_ppd(mmu_get_ppd())

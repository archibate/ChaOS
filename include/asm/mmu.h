#pragma once

#include <x86/cregs.h>
#include <bitops.h>

#define mmu_enablevm()	setcr0(getcr0() | CR0_PG)
#define mmu_disablevm()	setcr0(getcr0() & ~CR0_PG)
#define mmu_set_ppd(pd)	setcr3(pd)
#define mmu_get_ppd()	(getcr3() & MASKOF(PDWID))
#define mmu_invlpg(pg)	asm volatile ("invlpg (%0)\n" :: "r" (pg) : "cc", "memory")

#pragma once

#include <x86/tss.h>

extern struct tss tss0;

static inline ulong get_ksp(void)
{
	return tss0.ts_esp0;
}


static inline void set_ksp(ulong ksp)
{
	tss0.ts_esp0 = ksp;
}

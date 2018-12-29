#include <x86/tss.h>
#include <x86/gdt.h>
#include <x86/gate.h>
#include <x86/xdtr.h>
#include <stddef.h>

struct tss tss0;

void init_tss(unsigned long esp0)
{
	tss0.ts_ss0 = SEG_KDATA;
	tss0.ts_iomb = offsetof(struct tss, ts_iomap);
	tss0.ts_iomap[0] = 0xff;
	
	gdt[SEG_TSS0 >> 3] = SEGD16(STS_T32A, (ulong) &tss0, sizeof(tss0), 0);
	gdt[SEG_TSS0 >> 3].sd_s = 0;
	
	set_tr(SEG_TSS0);
}

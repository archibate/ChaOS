#include <x86/gdt.h>
#include <x86/xdtr.h>
#include <x86/sregs.h>

struct segdesc gdt[NGDT_ENTS] =
{
	[0]	= SEGD_NULL,
	[SEG_KCODE >> 3] = SEGD(STA_X | STA_R, 0x0, 0xffffffff, 0),
	[SEG_KDATA >> 3] = SEGD(STA_W,         0x0, 0xffffffff, 0),
	[SEG_UCODE >> 3] = SEGD(STA_X | STA_R, 0x0, 0xffffffff, 3),
	[SEG_UDATA >> 3] = SEGD(STA_W,         0x0, 0xffffffff, 3),
	[SEG_TSS0  >> 3] = SEGD_NULL,
};

void init_gdt(void)
{
	load_gdt(&gdt, sizeof(gdt));
	set_ss(SEG_KDATA);
	set_ds(SEG_KDATA);
	set_es(SEG_KDATA);
	set_fs(SEG_KDATA);
	set_gs(SEG_KDATA);
	set_cs(SEG_KCODE);
}

#pragma once

#include <mm/kbase.h>
#include <asm/iframe.h>
#include <mm/page.h>

struct pf_info
{
	ulong offset;
	uint errcd;
};

struct mt_page
{
	struct pf_info pfi;
	char padding[PGSIZE - (sizeof(struct mt_regs) + sizeof(struct pf_info))];
	struct mt_regs mtr;
};

#define mt_ax		mtr.ax
#define mt_cx		mtr.cx
#define mt_dx		mtr.dx
#define mt_bx		mtr.bx
#define pfi_offset	pfi.offset
#define pfi_errcd	pfi.errcd

#define $mtp ((struct mt_page *)MTPADDR)

#pragma once

#include <ccutils.h>
#include <mm/page.h>

typedef uint fporder_t;
typedef pgattr_t fpattr_t; // T: may not be a good name, try pgaccess_t??

#define PGA_INV		0	// N: assmued to be zero in any architecture
#define PGA_KRO		(PTE_P)
#define PGA_KRW		(PTE_P | PTE_W)
#define PGA_URO		(PTE_P | PTE_U)
#define PGA_URW		(PTE_P | PTE_W | PTE_U)
#define PGAMASK		(PTE_P | PTE_W | PTE_U)
#define PGA_VALID(pgattr)	PTE_VALID(pgattr)
#define PGA_WIDTH		3
#define PFN_WIDTH		(VAWID - PGWID)
#define ORDER_WIDTH		5 // x: (1<<5) = 32
#define FPGE_WIDTH		VAWID

typedef struct fpage
{
	pgattr_t	fp_attr		: PGA_WIDTH;
	fporder_t	fp_order	: ORDER_WIDTH;
	unsigned	fp_padding1	: FPGE_WIDTH - (PFN_WIDTH + PGA_WIDTH + ORDER_WIDTH);
	pfn_t		fp_pfn		: PFN_WIDTH;
}
_PACKED
fpage_t;

#define FPG_SIZE(fpg)	(1 << (fpg)->fp_order)
#define FPG_ATTR(fpg)	((fpg)->fp_attr)
#define FPG_PFN(fpg)	((fpg)->fp_pfn)
#define FPG_ORDER(fpg)	((fpg)->fp_order)
#define FPAGE(pfn, order, attr)	{ fp_attr: (attr), fp_order: (order), fp_pfn: (pfn), fp_padding1: 0 }

#pragma once

#ifndef _GPCPP_

#include <inttypes.h>

struct iframe
{
	ulong di, si, bp, osp, bx, dx, cx, ax;
	// --- page border ---
	ulong gs, fs, es, ds;
	ulong intnr, errcd;
	ulong pc, cs, eflags, sp, ss;
};
#endif

#define IFR_NMTRS	8
#define IFR_NPSRS	11
#define IFR_PSRSIZE	(__WORDSIZE__*IFR_NPSRS)

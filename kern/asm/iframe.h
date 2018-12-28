#pragma once

#include <inttypes.h>

struct iframe
{
	ulong di, si, bp, osp, bx, dx, cx, ax;
	ulong gs, fs, es, ds;
	ulong intnr, errcd;
	ulong pc, cs, eflags, sp, ss;
};

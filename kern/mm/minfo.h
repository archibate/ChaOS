#pragma once

#include <inttypes.h>

struct meminfo
{
	ulong beg, end;
};

extern struct meminfo meminfo;

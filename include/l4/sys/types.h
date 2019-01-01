#pragma once

#define MAX_PID		256
#define MAX_CHID	256


#include <inttypes.h>

typedef uint pid_t;
typedef uint chid_t;


#include <tol/region.h>

typedef _region_type(ulong) l4Region_t;

typedef struct l4FaultInfo
{
	ulong offset;
	uint errcd;
}
l4FaultInfo_t;

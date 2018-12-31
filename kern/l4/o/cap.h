#pragma once

#include <l4/objtypes.h>

/*
 * cap: Capability for some kind of Kernel Object
 */
typedef struct cap
{
	objtype_t type;
	void *ptr;
}
cap_t, *cptr_t;

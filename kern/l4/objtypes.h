#pragma once

#include <inttypes.h>

enum objtype
{
	L4_OBJ_UNTYPED = 0,
	L4_OBJ_TCB,
	L4_OBJ_FPAGE,
	L4_OBJ_VSPACE,
	L4_OBJTYPES,
};
typedef uint objtype_t;

enum
{
	L4_VSPACE_MAP = 1,
	L4_VSPACE_UNMAP = 2,
	L4_VSPACE_GRANT = 3,
};

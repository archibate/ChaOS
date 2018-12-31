#pragma once

#include <l4/objtypes.h>

#define OBJ_MAX_SIZE 12

typedef struct object
{
	objtype_t type;
	char raw[OBJ_MAX_SIZE];
}
obj_t;

long object_call(obj_t *op, long *a1, long *a2, long *a3);

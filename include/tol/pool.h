#pragma once

#include <stddef.h>

#define STATIC_POOL_TYPE(type, size, ...) struct __VA_ARGS__ { \
	type stk[size], *sp; \
}

#define pool_init(pool)		((pool)->sp = (pool)->stk)
#define pool_sizeof(pool)	(array_sizeof((pool)->stk))
#define pool_alloc(pool)	(*--(pool)->sp)
#define pool_free(pool, x)	(*(pool)->sp++ = (x))

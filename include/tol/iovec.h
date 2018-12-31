#pragma once

#include <size_t.h>

typedef struct iovec
{
	void *base;
	size_t len;
}
iovec_t;

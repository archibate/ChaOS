#pragma once

#include <ccutils.h>

void NORETURN _assert_failed(const char *info, const char *file,
							 const char *func, int line);

#define assert(x) assert_info(x, "assert("#x") failed")
#define assert_info(x, info) (unlikely(x) ? (void)0 : \
	_assert_failed(info, __FILE__, __FUNCTION__, __LINE__))

#define static_assert(x) \
	switch (0) { case 0: case (x): break; }

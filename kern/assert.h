#pragma once

#include <ccutils.h>

void NORETURN _assert(const char *expr, const char *file, int line);

#define assert(x) ((x) ? (void)0 : _assert(#x, __FILE__, __LINE__))

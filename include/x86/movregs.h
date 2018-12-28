#pragma once

#include <inttypes.h>

#define get_reg(reg) ({ \
	ulong __ret; \
	asm volatile ("mov %%"#reg", %0\n" : "=r" (__ret) :); \
	__ret; })

#define set_reg(reg, val, ...) \
	asm volatile ("mov %0, %%"#reg"\n" :: "r" (val) __VA_ARGS__)

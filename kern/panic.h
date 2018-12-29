#pragma once

#include <printk.h>
#include <asm/clsti.h>
#include <console.h>
#include <concolor.h>

#define _PANIC_PREFIX KL_PANIC "PANIC: "
#define panic(...) do { \
	printk(_PANIC_PREFIX __VA_ARGS__); \
	clihlt(); } while (0)

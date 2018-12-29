#pragma once

#include <inttypes.h>
#include "eflag-bits.h"

static uint get_eflags(void)
{
	uint eflags;
	asm volatile ("pushfl\npopl %0\n" : "=r" (eflags) :);
	return eflags;
}

static void set_eflags(uint eflags)
{
	asm volatile ("pushl %0\npopfl\n" :: "r" (eflags));
}

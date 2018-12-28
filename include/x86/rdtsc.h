#pragma once

#include <inttypes.h>

static uint32_t rdtsc_lo(void)
{
	uint32_t eax;
	asm volatile ("rdtsc" : "=a" (eax) :: "edx");
	return eax;
}

static uint32_t rdtsc_hi(void)
{
	uint32_t edx;
	asm volatile ("rdtsc" : "=d" (edx) :: "eax");
	return edx;
}

static uint64_t rdtsc(void)
{
	uint32_t eax, edx;
	asm volatile ("rdtsc" : "=a" (eax), "=d" (edx) :);
	return ((uint64_t)eax << 32) | edx;
}

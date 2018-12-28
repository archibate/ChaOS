#pragma once

#include <inttypes.h>

static uchar inb(ushort port)
{
	uchar data;
	asm volatile ("in %%dx, %%al\n" : "=a" (data) : "d" (port));
	return data;
}

static void outb(ushort port, uchar data)
{
	asm volatile ("out %%al, %%dx\n" :: "a" (data), "d" (port));
}

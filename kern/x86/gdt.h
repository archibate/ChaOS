#pragma once

#include <x86/segment.h>

#define SEG_KCODE 0x08
#define SEG_KDATA 0x10
#define SEG_UCODE 0x1b
#define SEG_UDATA 0x23
#define SEG_TSS0  0x28
#define NGDT_ENTS 6

extern struct segdesc gdt[NGDT_ENTS];

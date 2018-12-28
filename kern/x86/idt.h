#pragma once

#include <x86/gate.h>

#define INTR_IRQ0	64
#define INTR_SWI0	128
#define NIDT_ENTS   256

extern struct gatedesc idt[NIDT_ENTS];

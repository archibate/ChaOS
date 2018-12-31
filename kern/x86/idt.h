#pragma once

#include <x86/gate.h>
#include <l4/sysnr.h>

#define INTR_IRQ0	64
#define INTR_IRQMAX	128
#define INTR_SWI0	128
#define INTR_SWIMAX	(128+L4_SYSNRS)
#define NIDT_ENTS   256

extern struct gatedesc idt[NIDT_ENTS];

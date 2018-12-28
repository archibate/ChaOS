#pragma once

// https://blog.csdn.net/nerdx/article/details/14764753
#define IRQ_PIT		0
#define IRQ_KBD		1
#define IRQ_PIC1	2
#define IRQ_COM1	3
#define IRQ_COM0	4
#define IRQ_ATA1	5
#define IRQ_FLOPPY	6
#define IRQ_ATA0	7
#define IRQ_RTC		8
#define IRQ_MOUSE	12
#define IRQ_FPU		13
#define IRQ_IDE		14
#define NIRQS		16

typedef void (*irq_vec_t)(void);
extern irq_vec_t irq_vecs[NIRQS];

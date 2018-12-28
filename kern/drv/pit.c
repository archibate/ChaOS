#include <x86/io.h>
#include <drv/pic.h>
#include <x86/irqvecs.h>

// https://github.com/archibate/OS67/blob/master/kern/timer.c
#define IO_PIT_CNTL  0x43
#define IO_PIT_CTR0  0x40

void pit_set_timer(void (*timercb)(void), int hz)
{
	int ctr = 1193180 / hz;
	
	outb(IO_PIT_CNTL, 0x34);
	outb(IO_PIT_CTR0, ctr & 0xff);
	outb(IO_PIT_CTR0, ctr >> 8);
	
	irq_vecs[IRQ_PIT] = timercb;
	pic_irq_setenable(IRQ_PIT, 1);
}

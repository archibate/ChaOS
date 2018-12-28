#include <asm/iframe.h>
#include <x86/excpvecs.h>
#include <x86/irqvecs.h>
#include <x86/idt.h>
#include <drv/pic.h>
#include <printk.h>
#include <panic.h>
#include <stddef.h>

void hwintr(struct iframe *iframe)
{
	uint n = iframe->intnr;
	
	//printk(KL_DEBUG "hwintr(%d=%#x)", n);
	
	if (n < ARRAY_SIZEOF(excp_vecs))
		return excp_vecs[n](iframe);
	
	if (n >= INTR_IRQ0 && n < INTR_SWI0)
	{
		uint irq = n - INTR_IRQ0;
		if (irq < ARRAY_SIZEOF(irq_vecs) && irq_vecs[irq])
		{
			pic_irq_done(irq);
			return irq_vecs[irq]();
		}
	}
	
	panic("unhandled interrupt number %d=%#x!", n, n);
}

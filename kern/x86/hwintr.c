#include <asm/iframe.h>
#include <x86/excpvecs.h>
#include <x86/irqvecs.h>
#include <x86/idt.h>
#include <drv/pic.h>
#include <printk.h>
#include <panic.h>
#include <stddef.h>
#include <l4/syscall.h>

void hwintr(struct iframe *iframe)
{
	uint n = iframe->intnr;
	printk(KL_DEBUG "hwintr of %d(%#x)", n, n);
	
	if (n < ARRAY_SIZEOF(excp_vecs))
	{
		if (!excp_vecs[n])
			panic("Unhandled exception INT %d(%#x)", n, n);
		excp_vecs[n](iframe);
		return;
	}
	
	if (n >= INTR_IRQ0 && n < INTR_IRQMAX)
	{
		uint irq = n - INTR_IRQ0;
		if (irq < ARRAY_SIZEOF(irq_vecs) && irq_vecs[irq])
		{
			pic_irq_done(irq);
			irq_vecs[irq]();
			return;
		}
	}
	
	if (n >= INTR_SWI0 && n < INTR_SWIMAX)
	{
		uint nr = n - INTR_SWI0;
		system_call(nr, &iframe->mtr.ax, &iframe->mtr.cx, &iframe->mtr.dx, &iframe->mtr.bx);
		return;
	}
	
	panic("unhandled interrupt number %d=%#x!", n, n);
}

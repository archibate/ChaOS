#include <l4/vspace.h>
#include <mm/uvm.h>
#include <mm/pmm.h>
#define alloc_ppd()	zalloc_ppage()
#define free_ppd(x)	free_ppage(x)

void vspace_newinit(vspace_t *vs)
{
	pde_t *pgd = (pde_t*)KP2V(alloc_ppd());
	upd_setup_kvm(pgd);
	vs->pgd = pgd;
}

void vspace_delete(vspace_t *vs)
{
	pa_t ppd = KV2P((va_t)vs->pgd);
	free_ppd(ppd);
	vs->pgd = 0;
}

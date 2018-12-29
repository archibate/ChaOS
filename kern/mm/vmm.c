#include <mm/vmm.h>
#include <mm/pmm.h>
#include <memory.h>
#include <mm/kbase.h>
#include <printk.h>
#include <assert.h>

#define alloc_ppt() zalloc_ppage()

pte_t pd_getmap(pde_t *pd, pgva_t va)
{
	pde_t pde = pd[PDI(va)];
	if (!PDE_VALID(pde))
		return 0;

	pgpa_t ppt = PDE_PA(pde);
	pte_t *pt = (pte_t*)KP2V(ppt);
	
	return pt[PTI(va)];
}

pte_t pd_unmap(pde_t *pd, pgva_t va)
{
	pde_t pde = pd[PDI(va)];
	if (!PDE_VALID(pde))
		return 0;

	pgpa_t ppt = PDE_PA(pde);
	pte_t *pt = (pte_t*)KP2V(ppt);
	
	pte_t old_pte = pt[PTI(va)];
	pt[PTI(va)] = 0;
	return old_pte;
}

pte_t pd_map(pde_t *pd, pgva_t va, pte_t pte)
{
	pde_t pde = pd[PDI(va)];
	pa_t ppt;
	if (!PDE_VALID(pde))
	{
		ppt = alloc_ppt();
		printk("allocated: ppt=%p", ppt);
		pde = ppt | PDE_P | PDE_W | PDE_U;
		pd[PDI(va)] = pde;
	}
	else
	{
		ppt = PDE_PA(pde);
		printk("already: ppt=%p", ppt);
	}
	
	pte_t *pt = (pte_t*)KP2V(ppt);
	pte_t old_pte = pt[PTI(va)];
	pt[PTI(va)] = pte;
	
	printk("va=%p, pde=%p, pte=%p setted", va, pde, pte);
	
	return old_pte;
}

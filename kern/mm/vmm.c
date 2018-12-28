#include <mm/vmm.h>
#include <mm/pmm.h>
#include <memory.h>
#include <mm/kbase.h>
#include <printk.h>

pa_t alloc_ppt(void)
{
	pa_t ppt = alloc_ppage();
	pte_t *pt = (pte_t*)KP2V(ppt);
	memset(pt, 0, PTSIZE);
	return ppt;
}

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
	pde_t *p_pde = &pd[PDI(va)];
	pa_t ppt;
	if (!PDE_VALID(*p_pde))
	{
		ppt = alloc_ppt();
		*p_pde = ppt | PDE_P | PDE_W | PDE_U;
	}
	else
	{
		ppt = PDE_PA(*p_pde);
	}
	
	pte_t *pt = (pte_t*)KP2V(ppt);
	pt[PTI(va)] = pte;
}

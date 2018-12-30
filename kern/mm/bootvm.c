#include <mm/page.h>
#include <mm/kbase.h>
#include <ccutils.h>

#define boot_pd   ((pde_t*)0x100000)
#define boot_ptes ((pte_t*)0x101000)
#define kern_ptes KP2V(boot_ptes)
#define kern_pd   KP2V(boot_pd)

//extern pde_t boot_pd  [PDENTS]          ALIGNED(PDSIZE);
//extern pte_t kern_ptes[VA_VFI(PHYSTOP)] ALIGNED(PTSIZE);

pa_t init_afterbootvm(void)
{
	pa_t pa;
	for (pa = 0; pa < PSTOPMAX; pa += PGSIZE)
		kern_ptes[PFN(pa)] = PTE(pa, PTE_P | PTE_K | PTE_W);
	
	for (pa = 0; pa < PSTOPMAX; pa += PGSIZE * PTENTS) {
		pa_t  pta = KV2P((va_t)&kern_ptes[PFN(pa)]);
		pde_t pde = PDE(pta, PDE_P | PDE_K | PDE_W);
		kern_pd[PDI(KP2V(pa))] = pde;
		kern_pd[PDI(pa)] = 0;
	}
	
	return KV2P((va_t)kern_pd);
}

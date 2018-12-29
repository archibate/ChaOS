#include <mm/page.h>
#include <mm/kbase.h>
#include <asm/mmu.h>
#include <ccutils.h>

#define boot_pd   ((pde_t*)0x100000)
#define boot_ptes ((pte_t*)0x101000)
#define kern_ptes KP2V(boot_ptes)
#define kern_pd   KP2V(boot_pd)

//extern pde_t boot_pd  [PDENTS]         ;// ALIGNED(PDSIZE);
//extern pte_t kern_ptes[VA_VFI(PHYSTOP)];// ALIGNED(PTSIZE);

void __section(".phys.text") init_bootvm(void)
{
	pa_t pa;
	for (pa = 0; pa < PSTOPMAX; pa += PGSIZE)
		boot_ptes[PFN(pa)] = PTE(pa, PTE_P | PTE_K | PTE_W);
	
	for (pa = 0; pa < PSTOPMAX; pa += PGSIZE * PTENTS) {
		pa_t  pta = (va_t)&boot_ptes[PFN(pa)];
		pde_t pde = PDE(pta, PDE_P | PDE_K | PDE_W);
		boot_pd[PDI(KP2V(pa))] = pde;
		boot_pd[PDI(pa)] = pde;
	}
	
	mmu_set_ppd(boot_pd);
	mmu_enablevm();
}

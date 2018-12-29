#include <mm/uvm.h>
#include <mm/mmu.h>
#include <mm/vmm.h>
#include <mm/pmm.h>
#include <mm/umem.h>
#include <mm/kbase.h>
#include <asm/touser.h>
#include <printk.h>

static void pd_maps(pde_t *pd, va_t vstart, va_t vend, pte_t pte0)
{
	va_t va;
	pte_t pte = pte0;
	for (va = vstart; va < vend; va += PGSIZE)
	{
		pd_map(pd, va, pte);
		pte += PGSIZE;
	}
}

static void pd_newpgs(pde_t *pd, va_t vstart, va_t vend, uint pte_attr)
{
	va_t va;
	for (va = vstart; va < vend; va += PGSIZE)
	{
		pa_t ppg = alloc_ppage();
		pd_map(pd, va, PTE(ppg, pte_attr));
	}
}

#define alloc_ppd() zalloc_ppage()

void init_user(void)
{
	pde_t *upd = (pde_t*)KP2V(alloc_ppd());
	upd_setup_kvm(upd);
	
	extern char sigma0_beg[], sigma0_end[];
	pa_t beg = KV2P((va_t)&sigma0_beg);
	pa_t end = KV2P((va_t)&sigma0_end);
	
	int stksz = 10 * PGSIZE;
	
	pd_maps(upd, UBASE, UBASE + (end - beg),
			PTE(beg, PTE_P | PTE_W | PTE_U));
	/*pd_newpgs(upd, USTKTOP - PGSIZE - stksz, USTKTOP - PGSIZE,
			PTE_P | PTE_W | PTE_U);*/
	
	mmu_set_pd(upd);
	
	transfer_to_user(UBASE, USTKTOP - 16);
}

#include <mm/page.h>
#include <mm/kbase.h>
#include <mm/uvm.h>
#include <mm/mmu.h>
#include <printk.h>
#include <memory.h>
#include <mm/pmm.h>
#include <mm/vmm.h>

void upd_setup_kvm(pde_t *upd)
{
	pde_t *cpd = mmu_get_pd();
	memcpy(upd + PDI(KBASE), cpd + PDI(KBASE), sizeof(pde_t) * PDI(PSTOPMAX));
}

void upd_destroy_uvm(pde_t *upd)
{
	memset(upd, 0, sizeof(pde_t) * PDI(KBASE));
	memset(upd + PDI(KBASE) + PDI(PSTOPMAX), 0, sizeof(pde_t) * (PDENTS - (PDI(KBASE) + PDI(PSTOPMAX))));
}

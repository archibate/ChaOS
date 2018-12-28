#include <mm/page.h>
#include <mm/kbase.h>
#include <mm/uvm.h>
#include <mm/mmu.h>
#include <printk.h>
#include <memory.h>

void upd_setup_kvm(pde_t *upd)
{
	pde_t *cpd = mmu_get_pd();
	//memcpy(upd, cpd, PDSIZE);
	memcpy(upd + PDI(KBASE), cpd + PDI(KBASE), PDI(PHYSTOP) * sizeof(pde_t));
}

void upd_destroy_uvm(pde_t *upd)
{
	memset(upd, 0, PDI(KBASE));
}

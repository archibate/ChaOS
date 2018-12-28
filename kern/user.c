#include <mm/uvm.h>
#include <mm/mmu.h>
#include <mm/vmm.h>
#include <mm/umem.h>
#include <mm/kbase.h>

extern char initrd_beg[], initrd_end[];

void init_user(void)
{
	pde_t *upd = (pde_t*)KP2V(0x60000);
	upd_setup_kvm(upd);
	
	pa_t pa = KV2P((va_t)&initrd_beg);
	pd_map(upd, UBASE, PTE(pa, PTE_P | PTE_W | PTE_U));
	
	mmu_set_pd(upd);
}

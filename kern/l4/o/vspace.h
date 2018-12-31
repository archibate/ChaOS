#pragma once

#include <l4/fpage.h>
#include <mm/page.h>
typedef pde_t *pgdir_t;

// vspace: Virtual Space (or called Address Space) a process owns
typedef struct vspace
{
	pgdir_t pgd; // Pointer to Page Directory
}
vspace_t, proc_vspace_t;


void vspace_newinit(vspace_t *vs);
void vspace_delete(vspace_t *vs);


#include <mm/vmm.h>
#include <assert.h>

static pginfo_t vs_map(vspace_t *vs, pgva_t va, pginfo_t pgi)
{
	assert(vs->pgd);
	return pd_map(vs->pgd, va, pgi);
}

static pginfo_t vs_getmap(vspace_t *vs, pgva_t va)
{
	assert(vs->pgd);
	return pd_getmap(vs->pgd, va);
}

static pginfo_t vs_unmap(vspace_t *vs, pgva_t va)
{
	assert(vs->pgd);
	return pd_unmap(vs->pgd, va);
}


#include <mm/mmu.h>

static void vspace_use(vspace_t *vs)
{
	assert(vs->pgd);
	mmu_set_pd(vs->pgd);
}

/* T: vs_mapcap(vs, vstart, cap) */

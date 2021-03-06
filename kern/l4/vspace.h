#pragma once

#include <mm/page.h>

typedef pde_t *pgdir_t;
typedef pte_t pginfo_t;
typedef uint pgattr_t; // T: may not be a good name, try pgaccess_t??

#define PGA_INV	0	// N: assmued to be zero in any architecture
#define PGA_KRO	(PTE_P)
#define PGA_KRW	(PTE_P | PTE_W)
#define PGA_URO	(PTE_P | PTE_U)
#define PGA_URW	(PTE_P | PTE_W | PTE_U)
#define PGAMASK	(PTE_P | PTE_W | PTE_U)
#define PGINFO(pa, type)	PTE(pa, type)
#define PGI_PADR(pgi)		((pgi) & PGMASK)
#define PGI_PGA(pgi)		((pgi) & PGAMASK)
#define PGI_VALID(pgi)		PTE_VALID(pgi)


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

static pginfo_t vs_map(vspace_t *vs, va_t va, pginfo_t pgi)
{
	assert(vs->pgd);
	return pd_map(vs->pgd, va, pgi);
}

static pginfo_t vs_getmap(vspace_t *vs, va_t va)
{
	assert(vs->pgd);
	return pd_getmap(vs->pgd, va);
}

static pginfo_t vs_unmap(vspace_t *vs, va_t va)
{
	assert(vs->pgd);
	return pd_unmap(vs->pgd, va);
}

#include <mm/pmm.h>

static int vs_map_s(vspace_t *vs, va_t va, pginfo_t pginfo)
{
	pginfo = vs_map(vs, va, pginfo);
	if (!PGI_VALID(pginfo))
		return 0;
	try_free_ppage(PGI_PADR(pginfo));
	return 1;
}

static int vs_unmap_s(vspace_t *vs, va_t va)
{
	pginfo_t pginfo = vs_unmap(vs, va);
	if (!PGI_VALID(pginfo))
		return 0;
	try_free_ppage(PGI_PADR(pginfo));
	return 1;
}

#include <mm/mmu.h>

static void vspace_use(vspace_t *vs)
{
	assert(vs->pgd);
	mmu_set_pd(vs->pgd);
}

/* T: vs_mapcap(vs, vstart, cap) */

#pragma once

#include <inttypes.h>
#include <asm/page.h>

typedef ulong va_t, pgva_t;
typedef ulong pa_t, pgpa_t;
typedef pa_t pte_t;
typedef pa_t pde_t;

#define PFN(a)    ((a) >> PGWID)
#define PDI(a)    (PFN(a) >> PTWID)
#define PTI(a)    (PFN(a) & OFFMOF(PTWID))
#define PAG(pfn)  ((pfn) << PGWID)

#define PDE(pa, attr) (PDE_PA(pa) | PDE_ATTR(attr))
#define PTE(pa, attr) (PTE_PA(pa) | PTE_ATTR(attr))

#define PTE_ATTR(pte) ((pte) & OFFMOF(PTWID))
#define PTE_PA(pte)   ((pte) & MASKOF(PDWID))
#define PDE_ATTR(pde) ((pde) & OFFMOF(PTWID))
#define PDE_PA(pde)   ((pde) & MASKOF(PDWID))

#define PDE_VALID(pde) ((pde) & PDE_P)
#define PTE_VALID(pte) ((pte) & PTE_P)

#define PGUP(x) ((x + PGSIZE - 1)	& PGMASK)
#define PGDN(x) ((x)				& PGMASK)


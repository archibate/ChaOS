#pragma once

#ifndef _GPCPP_
#include <inttypes.h>
#endif
#include <asm/page-bits.h>
#include <tol/bitops.h>

#define PGSIZE  ENTSOF(PGWID)
#define PTENTS  ENTSOF(PTWID)
#define PDENTS  ENTSOF(PDWID)
#define PTSIZE  (PTENTS*__WORDSIZE__)
#define PDSIZE  (PDENTS*__WORDSIZE__)

#define PGMASK	MASKOF(PGWID)
#define PTMASK	MASKOF(PTWID)
#define PDMASK	MASKOF(PDWID)
#define PGOFFM	OFFMOF(PGWID)
#define PTOFFM	OFFMOF(PTWID)
#define PDOFFM	OFFMOF(PDWID)

#ifndef _GPCPP_
typedef ulong va_t, pgva_t;
typedef ulong pa_t, pgpa_t;
typedef ulong vpn_t;
typedef ulong pfn_t;
typedef uint pgoff_t;
typedef pa_t pte_t;
typedef pa_t pde_t;
#endif

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

#define PGUP(x)		((x + PGSIZE - 1) & PGMASK)
#define PGDN(x)		((x) & PGMASK)
#define PGOFF(x)	((x) & PGOFFM)


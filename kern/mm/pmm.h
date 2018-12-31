#pragma once

#include <mm/page.h>
#include <tol/pool.h>
#include <mm/kbase.h>

#define PPM_NPAGES ((PPMAXEND - PPMBEG) / PGSIZE)

pa_t alloc_ppage(void);
pa_t zalloc_ppage(void);
void free_ppage(pa_t pa);
int try_free_ppage(pa_t pa);

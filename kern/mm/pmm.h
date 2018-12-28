#pragma once

#include <mm/page.h>
#include <tol/pool.h>

#define PPM_NPAGES 256

typedef STATIC_POOL_TYPE(pa_t, PPM_NPAGES, ppm_pool_struct) __ppm_pool_t;
extern __ppm_pool_t _pmm_pool;

#define alloc_ppage()	pool_alloc(&_pmm_pool)
#define free_ppage(pa)	pool_free(&_pmm_pool, pa)

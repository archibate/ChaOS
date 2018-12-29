#include <mm/pmm.h>
#include <mm/page.h>
#include <mm/kbase.h>
#include <memory.h>
#include <assert.h>

static STATIC_POOL_TYPE(pa_t, PPM_NPAGES) pmm_pool;

pa_t alloc_ppage(void)
{
	assert_info(pool_rested(&pmm_pool) > 0, "Out of Memory");
	pa_t pa = pool_alloc(&pmm_pool);
	assert(PPMBEG <= pa && pa < PPMEND);
	return pa;
}

void free_ppage(pa_t pa)
{
	assert(pool_usage(&pmm_pool) > 0);
	assert(PPMBEG <= pa && pa < PPMEND);
	pool_free(&pmm_pool, pa);
}

pa_t zalloc_ppage(void)
{
	pa_t ppg = alloc_ppage();
	void *pg = (void*)KP2V(ppg);
	memset(pg, 0, PTSIZE);
	return ppg;
}

void init_pmm(void)
{
	pa_t pa;
	pool_init(&pmm_pool);
	for (pa = PPMBEG; pa < PPMEND; pa += PGSIZE)
		free_ppage(pa);
}

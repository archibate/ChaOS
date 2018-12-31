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
	assert(PPMBEG <= pa && pa < PPMEND);
	assert(pool_usage(&pmm_pool) > 0);
	pool_free(&pmm_pool, pa);
}

int try_free_ppage(pa_t pa)
{
	if (!(PPMBEG <= pa && pa < PPMEND))
		return 0;
	assert(pool_usage(&pmm_pool) > 0);
	pool_free(&pmm_pool, pa);
	return 1;
}

pa_t zalloc_ppage(void)
{
	pa_t ppg = alloc_ppage();
	void *pg = (void*)KP2V(ppg);
	/*printk("pg=%p", pg);
	*(volatile int*)pg;
	static int i;
	if (i) asm volatile ("cli;hlt");
	if (!i) i = 1;*/
	memset(pg, 0, PGSIZE);
	return ppg;
}

void init_pmm(void)
{
	pa_t pa;
	pool_init(&pmm_pool);
	for (pa = PPMEND - PGSIZE; pa >= PPMBEG; pa -= PGSIZE)
		free_ppage(pa);
}

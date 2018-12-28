#include <mm/pmm.h>

__ppm_pool_t _pmm_pool;

void init_pmm(void)
{
	pool_init(&_pmm_pool);
}
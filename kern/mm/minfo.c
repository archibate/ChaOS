#include <mm/minfo.h>
#include <mm/kbase.h>
#include <ccutils.h>
#include <memory.h>
#include <printk.h>

#define MTEST_BEG PPMBEG
#define MTEST_END PSTOPMAX

struct meminfo meminfo =
{
	.beg = MTEST_BEG,
	.end = MTEST_END,
};

void __section(".phys.text") init_boot_meminfo(void)
{
	extern void memory_test(ulong *p_start, size_t *p_size);
	struct meminfo *bminfo = KV2P(&meminfo);
	size_t size = bminfo->end - bminfo->beg;
	memory_test(&bminfo->beg, &size);
	bminfo->end = bminfo->beg + size;
}

void init_meminfo(void)
{
	printk(KL_INFO "meminfo #1: %p to %p", meminfo.beg, meminfo.end);
}

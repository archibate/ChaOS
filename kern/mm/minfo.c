#include <mm/minfo.h>
#include <ccutils.h>
#include <memory.h>
#include <printk.h>

#define MTEST_BEG 0x200000
#define MTEST_END 0x20000000

static struct meminfo __section(".phys.data") _bminfo =
{
	.beg = MTEST_BEG,
	.end = MTEST_END,
};

struct meminfo meminfo;

void __section(".phys.text") init_boot_meminfo(void)
{
	extern void memory_test(ulong *p_start, size_t *p_size);
	size_t size = _bminfo.end - _bminfo.beg;
	memory_test(&_bminfo.beg, &size);
	_bminfo.end = _bminfo.beg + size;
}

void init_meminfo(void)
{
	memcpy(&meminfo, &_bminfo, sizeof(meminfo));
	printk(KL_INFO "meminfo #1: %p to %p", meminfo.beg, meminfo.end);
}

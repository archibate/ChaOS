#include <l4/syscall.h>
#include <printk.h>

long system_call(int nr, long a1, long a2, long a3)
{
	printk("system_call(nr=%d, a1=%d, a2=%d, a3=%d)", nr, a1, a2, a3);
}

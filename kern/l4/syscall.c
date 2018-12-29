#include <l4/syscall.h>
#include <printk.h>

int system_call(long a1, long a2, long a3)
{
	printk("system_call(a1=%d, a2=%d, a3=%d)", a1, a2, a3);
}

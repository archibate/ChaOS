#include <drv/pit.h>
#include <printk.h>

static void on_timer(void)
{
	printk(KL_DEBUG "on_timer!");
}

void init_timer(void)
{
	pit_set_timer(on_timer, 100);
}

#include <conio.h>
#include <printk.h>
#include <asm/clsti.h>
#include <ccutils.h>

#define CALL(x, ...) do { extern void x(); x(__VA_ARGS__); } while (0)

void kern_main(void)
{
	CALL(init_vga);
	cputs("done\n\n");
	printk(KL_INFO "starting version 001");
	
	printk(KL_INFO "init_meminfo");
	CALL(init_meminfo);
	printk(KL_INFO "init_idt");
	CALL(init_idt);
	printk(KL_INFO "init_gdt");
	CALL(init_gdt);
	printk(KL_INFO "init_tss");
	CALL(init_tss);
	printk(KL_INFO "init_pic");
	CALL(init_pic);
	printk(KL_INFO "init_timer");
	CALL(init_timer);
	printk(KL_INFO "init_pmm");
	CALL(init_pmm);
	printk(KL_INFO "init_user");
	CALL(init_user);
	
	printk(KL_INFO "entering idle loop");
	for (;;)
		stihlt();
}


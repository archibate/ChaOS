#include <drv/vga.h>
#include <conio.h>
#include <mm/umem.h>

void sigma0_main(void)
{
	setup_vga_console((void*)USRVRAM);
	cputs("done\nSigma0 started!\n");
	
	asm volatile ("int $0x80" :: "a" (2018), "c" (12), "d" (29));
	asm volatile ("int $0x81" :: "a" (2018), "c" (12), "d" (30));
	asm volatile ("int $0x82" :: "a" (2019), "c" (1), "d" (1));
}

#include <drv/vga.h>
#include <mm/umem.h>
#include <conio.h>
#include <l4/sys/ipc.h>

void sigma0_main(void)
{
	setup_vga_console((void*)USRVRAM);
	cputs("done\n\nSigma0 started!\n");

	char msg[] = "Hello, World!\n";

	l4MsgInfo_t mi;
	l4miSetLongMsg(&mi, &msg, sizeof(msg));
	l4Call(2, &mi, &mi);

	l4Wait(1, &mi);
	iovec_t iov = l4miGetLongMsgv(&mi);
	cprintf("l4Wait resulted: %.*s\n", iov.len, iov.base);
	//asm volatile ("cli;hlt");
	
	//asm volatile ("int $0x80" :: "a" (2018), "c" (12), "d" (29));
	//asm volatile ("int $0x81" :: "a" (2018), "c" (12), "d" (30));
	//asm volatile ("int $0x82" :: "a" (2019), "c" (1), "d" (1));
	//asm volatile ("int $0x83" :: "a" (2019), "c" (1), "d" (2));
}

#include <l4/sys/chans.h>
#include <l4/sys/ipc.h>
#include <drv/vga.h>
#include <mm/umem.h>
#include <conio.h>

void sigma0_main(void)
{
	setup_vga_console((void*)USRVRAM);
	cputs("done\n\nSigma0 started!\n");

	l4FaultInfo_t fi;
	l4Wait(L4CH_Sigma0, &fi);
	cprintf("sigma0 caught fault offset=%#x, errcd=%d\n", fi.offset, fi.errcd);
}

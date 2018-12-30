#include <console.h>
#include <conio.h>
#include <x86/io.h>
#include <mm/kbase.h>
#include <div.h>

#define IO_VGA_CRT  0x3d4

static void vga_con_enter(struct console *con)
{
	outb(IO_VGA_CRT+0, 0xe);
	int hi = inb(IO_VGA_CRT+1);
	outb(IO_VGA_CRT+0, 0xf);
	int lo = inb(IO_VGA_CRT+1);
	int off = (hi << 8) | lo;
	div_t d = div(off, con->scrnx);
	con_setcur(con, d.rem, d.quot);
}

static void vga_con_leave(struct console *con)
{
	int off = con->cy * con->scrnx + con->cx;
	outb(IO_VGA_CRT+0, 0xe);
	outb(IO_VGA_CRT+1, off >> 8);
	outb(IO_VGA_CRT+0, 0xf);
	outb(IO_VGA_CRT+1, off & 0xff);
}

static struct console vga_con;

void init_vga(void)
{
	vga_con.buf = (struct con_char *)KP2V(0xb8000);
	vga_con.scrnx = 80;
	vga_con.scrny = 25;
	vga_con.enter = vga_con_enter;
	vga_con.leave = vga_con_leave;
	con_init(&vga_con);
	vga_con_enter(&vga_con);
	conio_con = &vga_con;
}

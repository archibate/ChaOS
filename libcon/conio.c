#include <conio.h>
#include <console.h>
#include <sprintf.h>
#include <stdarg.h>

struct console *conio_con;

void cputs(const char *s)
{
	con_puts(conio_con, s);
}

void cputchar(char ch)
{
	con_putchar(conio_con, ch);
}

int vcprintf(const char *fmt, va_list ap)
{
	char buf[256];
	int ret = vsprintf(buf, fmt, ap);
	cputs(buf);
	return ret;
}

int cprintf(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	int ret = vcprintf(fmt, ap);
	va_end(ap);
	return ret;
}

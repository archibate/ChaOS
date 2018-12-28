#include <printk.h>
#include <sprintf.h>
#include <x86/rdtsc.h>
#include <conio.h>

void syslog(const char *s)
{
	int loglev = DEFAULT_MESSAGE_LOGLEVEL;
	if (s[0] == '<' && s[1] && s[2] == '>')
	{
		loglev = s[1] - '0';
		s += 3;
	}
	if (loglev <= DEFAULT_CONSOLE_LOGLEVEL)
		cprintf("[%10u%c] %s\n", rdtsc_lo(), "pacewnid---"[loglev], s);
}

int vprintk(const char *fmt, va_list ap)
{
	char buf[256];
	int ret = vsprintf(buf, fmt, ap);
	syslog(buf);
	return ret;
}

int printk(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	int ret = vprintk(fmt, ap);
	va_end(ap);
	return ret;
}

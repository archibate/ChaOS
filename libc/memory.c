//#include "memory.h" // xuxuxu!
#include <wchar.h>

void memcpy(char *dst, const char *src, unsigned long n)
{
	while (n--)
		*dst++ = *src++;
}

void memrcpy(char *dst, const char *src, unsigned long n)
{
	dst += n;
	src += n;
	while (n--)
		*--dst = *--src;
}

int memcmp(const char *dst, const char *src, unsigned long n)
{
	int res = 0;
	while (n-- && (res = *dst++ - *src++));
	return res;
}

void memset(char *dst, char val, unsigned long n)
{
	while (n--)
		*dst++ = val;
}

void memsetw(wchar_t *dst, wchar_t val, unsigned long n)
{
	while (n--)
		*dst++ = val;
}

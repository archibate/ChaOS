#pragma once


void memcpy(void *dst, const void *src, unsigned long n);
void memrcpy(void *dst, const void *src, unsigned long n);
int memcmp(const void *dst, const void *src, unsigned long n);
void memsetw(unsigned short *dst, unsigned short val, unsigned long n);
void memset(void *dst, char val, unsigned long n);

static inline void memmove(void *dst, const void *src, unsigned long n)
{
	if (dst > src)
		return memrcpy(dst, src, n);
	else
		return memcpy(dst, src, n);
}

static inline volatile void *bzero
(volatile void *dst, unsigned long n)
{
	memset((void *) dst, 0, n);
	return dst;
}

static inline volatile void *bcopy
(const volatile void *src, volatile void *dst, unsigned long n)
{
	memcpy((void *) dst, (const void *) src, n);
	return dst;
}

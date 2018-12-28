#pragma once


typedef struct _div_t {
	unsigned int quot, rem;
} div_t;

typedef struct _ldiv_t {
	unsigned long quot, rem;
} ldiv_t;


static div_t div(unsigned int a, unsigned int b)
{
	div_t d = { a / b, a % b };
	return d;
}

static ldiv_t ldiv(unsigned long a, unsigned long b)
{
	ldiv_t d = { a / b, a % b };
	return d;
}

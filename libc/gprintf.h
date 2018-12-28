#pragma once


#include <stdarg.h>
#include <ccutils.h>


int vgprintf
	( void (*putch)(char)
	, const char *fmt
	, va_list ap
	);

int gprintf
	( void (*putch)(char)
	, const char *fmt
	, ...
	) _FORMAT(printf, 2, 3);

#pragma once

#include <stdarg.h>

extern struct console *conio_con;

void cputchar(char ch);
void cputs(const char *s);
int vcprintf(const char *fmt, va_list ap);
int cprintf(const char *fmt, ...);

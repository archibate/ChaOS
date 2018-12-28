#pragma once

#include <size_t.h>
#include <concolor.h>

struct con_color
{
	char fc: 4;
	char bc: 4;
};

struct con_char
{
	char ch;
	struct con_color clr;
};

struct console
{
	struct con_char *buf;
	struct con_color color;
	int cx, cy, oldcx, oldcy;
	int scrnx, scrny;
	void (*enter)(struct console *);
	void (*leave)(struct console *);
};

void con_init(struct console *con);
size_t con_write(struct console *con, const char *s, size_t n);
void con_putchar(struct console *con, char c);
void con_puts(struct console *con, const char *s);
void con_clear(struct console *con);
void con_setcur(struct console *con, int x, int y);
void con_getcur(struct console *con, int *px, int *py);

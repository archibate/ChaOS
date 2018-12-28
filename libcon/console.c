// https://github.com/archibate/OS67/blob/master/drv/vga.c
#include <console.h>
#include <memory.h>
#include <string.h>
#include <inttypes.h>

#define con_enter(con) (con)->enter(con)
#define con_leave(con) (con)->leave(con)

void con_init(struct console *con)
{
	con->color.bc = COL_BLACK;
	con->color.fc = COL_L_GREY;
	con->cx = con->cy = 0;
	con->oldcx = con->oldcy = 0;
	con_enter(con);
}

void con_setcur(struct console *con, int x, int y)
{
	if (x < 0) x = 0;
	if (x >= con->scrnx) x = con->scrnx;
	if (y < 0) y = 0;
	if (y >= con->scrny) y = con->scrny;
	con->cx = x;
	con->cy = y;
	con_leave(con);
}

void con_getcur(struct console *con, int *px, int *py)
{
	con_enter(con);
	*px = con->cx;
	*py = con->cy;
}

static ushort getblank(struct con_color color)
{
	union {
		struct con_char vc;
		ushort raw;
	} u = { .vc = {
		.ch = ' ',
		.clr = color,
	}};
	return u.raw;
}

void con_clear(struct console *con)
{
	memsetw((ushort*)con->buf, getblank(con->color), con->scrnx * con->scrny);
	con->cx = con->cy = 0;
	con_leave(con);
}

static void con_chk_scroll(struct console *con)
{
	int rel = con->cy - con->scrny;
	if (rel++ >= 0) {
		memcpy(con->buf, con->buf + con->scrnx,
			   con->scrnx * (con->scrny - rel) * sizeof(struct con_char));
		memsetw((ushort *)(con->buf + con->scrnx * (con->scrny - rel)),
				getblank(con->color), con->scrnx * rel);
		con->cy -= rel;
	}
}

static void __con_putchar(struct console *con, char ch)
{
	struct con_char *pixel;
	switch (ch) {
	case '\r':	con->cx = 0; break;
	case '\n':	con->cy++; con->cx = 0; break;
	case '\b':	//if (!con->cx) con->cy--;
				con->cx = (con->cx + con->scrnx - 1) % con->scrnx;
				pixel = &con->buf[con->cy * con->scrnx + con->cx];
				pixel->ch = ' ';
				pixel->clr = con->color;
				break;
	case '\t':	do con_putchar(con, ' '); while (con->cx % 4); break;
	default:	pixel = &con->buf[con->cy * con->scrnx + con->cx];
				pixel->ch = ch;
				pixel->clr = con->color;
				con->cy += (con->cx + 1) / con->scrnx;
				con->cx = (con->cx + 1) % 80;
	}
	con_chk_scroll(con);
}

void con_puts(struct console *con, const char *s)
{
	con_enter(con);
	con_write(con, s, strlen(s));
	con_leave(con);
}

#define XCHGI(x, y) do{ (x)^=(y); (y)^=(x); (x)^=(y); } while(0)

static void ansi_color(struct con_color *color, int num)
{
	switch (num) {
	case 0: color->fc = COL_L_GREY; return;
	case 1: color->fc |= COL_LIGHT_BIT; return;
	case 2: color->bc |= COL_LIGHT_BIT; return;
	case 7: XCHGI(color->fc, color->bc); return;
	case 8: color->fc = color->bc = 0; return;
	}
	num -= 30;
	if (0 <= num && num < 8) {
		color->fc &= ~COL_CLR_BITS;
		color->fc |= num;
		return;
	}
	num -= 10;
	if (0 <= num && num < 8) {
		color->bc &= ~COL_CLR_BITS;
		color->bc |= num;
		return;
	}
}

size_t con_write(struct console *con, const char *s, size_t n)
{
	int num, num_old;
	const char *end = s + n;
	con_enter(con);

	while (s < end) {
		if (s[0] == '\033' && s[1] == '[') {
			num_old = num = 0;

			for (s += 2; s < end; s++) {
				if ('0' <= *s && *s <= '9')
					num = 10 * num + *s - '0';
				else if (*s == ';')
					num_old = num;

				else {
					switch (*s++) {
					case 'm':
						if (num_old)
							ansi_color(&con->color, num_old);
						ansi_color(&con->color, num);
						break;
					case 'A': con->cy -= (num?num:1) * 16; if (con->cy < 0) con->cy = 0; break;
					case 'B': con->cy += (num?num:1) * 16; if (con->cy > con->scrny) con->cy = con->scrny; break;
					case 'C': con->cx += (num?num:1) * 8; if (con->cx > con->scrnx) con->cy = con->scrnx; break;
					case 'D': con->cx -= (num?num:1) * 8; if (con->cx < 0) con->cx = 0; break;
					//case 'a': moveright(AT(con->cx, con->cy), 8, (num?num:1) * 8); break;
					case 'J': con_clear(con); con->cy = 0; break;
					case 'K': while (con->cx < con->scrnx) __con_putchar(con, ' '); break;
					case 'H': con->cx = num; con->cy = num_old; break;
					case 's': con->oldcx = con->cx; con->oldcy = con->cy; break;
					case 'u': con->cx = con->oldcx; con->cy = con->oldcy; break;
					//case 'l': cur_min = 0; cur_max = 0; break;
					//case 'h': cur_min = num_old; cur_max = (num ? num : 3); break;
					}
					break;
				}
			}
		} else __con_putchar(con, *s++);
	}
	con_leave(con);
	return n;
}

void con_putchar(struct console *con, char c)
{
	con_enter(con);
	__con_putchar(con, c);
	con_leave(con);
}

#pragma once


#include <inttypes.h>
#include <ccutils.h>


#define get_xtrsel(xtr) ({ \
	uint __ret; \
	asm volatile ("s"#xtr" %%ax\n" : "=a" (__ret) ::); \
	return __ret; })
#define set_xtrsel(xtr, val, ...) \
	asm volatile ("l"#xtr" %%ax\n" :: "a" (val) __VA_ARGS__)

#define get_ldtr()    get_xtrsel(ldt)
#define set_ldtr(val) set_xtrsel(ldt, val)
#define get_tr()      get_xtrsel(tr)
#define set_tr(val)   set_xtrsel(tr, val)


// Pseudo-descriptors used for LGDT, LLDT and LIDT instructions.
struct x86_xdtr {
	uint16_t limit;		// Limit
	uintptr_t base;		// Base address
} PACKED;

#define store_xdtr(xdtname, xdtr) do { \
	const struct x86_xdtr *__xdtr = (xdtr); \
	asm volatile ("s"#xdtname" %0\n" :: "m" (*__xdtr) : "memory"); \
} while (0)
#define load_xdtr(xdtname, xdtr) do { \
	struct x86_xdtr *__xdtr = (xdtr); \
	asm volatile ("l"#xdtname" %0\n" :: "m" (*__xdtr) : "memory"); \
} while (0)

#define load_gdtr(gdtr)  load_xdtr(gdt, gdtr)
#define store_gdtr(gdtr) store_xdtr(gdt, gdtr)
#define load_idtr(idtr)  load_xdtr(idt, idtr)
#define store_idtr(idtr) store_xdtr(idt, idtr)

#define load_xdt(xdtname, xdt, size) do { \
	struct x86_xdtr __dtr = { .limit = (size) - 1, .base = (ulong)(xdt) }; \
	load_xdtr(xdtname, &__dtr); \
} while (0)

#define load_gdt(pgdt, size) load_xdt(gdt, pgdt, size)
#define load_idt(pidt, size) load_xdt(idt, pidt, size)

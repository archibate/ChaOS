#pragma once

#include <x86/movregs.h>

#define set_cs(cs) \
	asm volatile ("pushl %0\npushl $1f\nretf\n1:\n" :: "r" (cs));

#define get_sreg(xs)      get_reg(xs)
#define set_sreg(xs, val) set_reg(xs, val)

#define get_ss()     get_sreg(ss)
#define get_ds()     get_sreg(ds)
#define get_es()     get_sreg(es)
#define get_fs()     get_sreg(fs)
#define get_gs()     get_sreg(gs)
#define set_ss(val)  set_sreg(ss, val)
#define set_ds(val)  set_sreg(ds, val)
#define set_es(val)  set_sreg(es, val)
#define set_fs(val)  set_sreg(fs, val)
#define set_gs(val)  set_sreg(gs, val)

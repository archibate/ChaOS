#pragma once

#ifndef _GPCPP_
#include <mm/minfo.h>
#endif
#include <asm/iframe.h>
#include <mm/page.h>

#define KCODBEG  0x8000
#define KCODSTP  0x20000
#define PPMBEG   0x200000
#define PSTOPMAX 0x10000000
#define PHYSTOP  meminfo.end
#define PPMEND   PHYSTOP
#define PPMAXEND PSTOPMAX
#define KBASE    0xc0000000
#define KSTKTOP  (KBASE + PHYSTOP + IFR_MTRSIZE + IFR_PSRSIZE)
#define MTPADDR  (KBASE + PHYSTOP - PGSIZE)
#define KTMPADR  (KBASE + PHYSTOP + PGSIZE)
#ifndef _GPCPP_
#define KP2V(pa) ((typeof(pa))((ulong)(pa) + KBASE))
#define KV2P(va) ((typeof(va))((ulong)(va) - KBASE))
#else
#define KP2V(pa) ((pa) + KBASE)
#define KV2P(va) ((va) - KBASE)
#endif

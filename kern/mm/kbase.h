#pragma once

#include <mm/minfo.h>

#define KCODBEG  0x8000UL
#define KCODSTP  0x10000UL
#define PPMBEG   0x100000UL
#define PHYSTOP  meminfo.end
#define PPMEND   PHYSTOP
#define PPMAXEND PSTOPMAX
#define PSTOPMAX 0x10000000UL
#define KBASE    0xc0000000UL
#define KP2V(pa) ((typeof(pa))((ulong)(pa) + KBASE))
#define KV2P(va) ((typeof(va))((ulong)(va) - KBASE))

#pragma once

#include <mm/minfo.h>

#define PHYSTOP  meminfo.end//0x10000000
#define KBASE    0xc0000000
#define KP2V(pa) ((typeof(pa))((ulong)(pa) + KBASE))
#define KV2P(va) ((typeof(va))((ulong)(va) - KBASE))

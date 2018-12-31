#pragma once

#include <l4/sysnr.h>

void system_call(sysnr_t nr, long *a0, long *a1, long *a2, long *a3);

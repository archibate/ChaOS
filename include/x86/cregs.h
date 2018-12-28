#pragma once

#include <x86/movregs.h>
#include "creg-bits.h"

#define getcr2()     get_reg(cr2)
#define getcr0()     get_reg(cr0)
#define setcr0(val)  set_reg(cr0, val)
#define getcr3()     get_reg(cr3)
#define setcr3(val)  set_reg(cr3, val, : "cc", "memory")
#define getcr4()     get_reg(cr4)
#define setcr4(val)  set_reg(cr4, val)

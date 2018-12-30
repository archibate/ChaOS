#pragma once

#include <l4/cap.h>

// cspace: Capabilities Space a process owns
typedef struct cspace
{
	cap_t c;
}
cspace_t, proc_cspace_t;
// n: When a page fault occurred in a process (not found in vspace),
//    the pagger should check its cspace for, if any CAP_MEM matches
//    the fault address, map it! elsewhile, kill(SIGSEGV)

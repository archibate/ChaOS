#pragma once

#include <l4/vspace.h>
#include <l4/cspace.h>

typedef struct proc
{
	proc_vspace_t vs;
	proc_cspace_t cs;
}
proc_t;

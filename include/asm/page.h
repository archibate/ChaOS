#pragma once

#include <asm/page-bits.h>
#include <bitops.h>

#define PGSIZE  ENTSOF(PGWID)
#define PTENTS  ENTSOF(PTWID)
#define PDENTS  ENTSOF(PDWID)
#define PTSIZE  (PTENTS*sizeof(long))
#define PDSIZE  (PDENTS*sizeof(long))

#define PGMASK	MASKOF(PGWID)
#define PTMASK	MASKOF(PTWID)
#define PDMASK	MASKOF(PDWID)
#define PGOFFM	OFFMOF(PGWID)
#define PTOFFM	OFFMOF(PTWID)
#define PDOFFM	OFFMOF(PDWID)

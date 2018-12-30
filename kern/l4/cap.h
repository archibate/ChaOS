#pragma once

// ca: Caping Address, Physical Address for CAP_MEM, I/O Port No. for CAP_IOPORT, etc.
typedef pa_t ca_t; // simply use the widest now :)

// captype: Type of a Capability, CAP_MEM for Memory, CAP_IOPORT for x86 I/O Port
typedef enum captype
{
	CAP_UNINIT = 0,
	CAP_MEM,
	CAP_IOPORT,
} captype_t;

// cap: Capability for some kind of resources in range of [beg, end)
typedef struct cap
{
	ca_t beg, end;
	captype_t type;
}
cap_t;

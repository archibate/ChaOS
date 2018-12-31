#pragma once

#include <l4/vspace.h>
#include <tol/region.h>

// cap: Capability region of [beg, end)
typedef _region_type(ca_t, cregion) cregion_t;

// ca: Caping Address, Physical Address for CAP_MEM, I/O Port No. for CAP_IOPORT, etc.
typedef pa_t ca_t; // use the widest possible :)

// cattr: Capablity Attribute (or called Access Rights), Readonly? Kernel? etc.
typedef pgattr_t cattr_t;
#define CA_INV			PGA_INV
#define CA_RO			PGA_URO
#define CA_RW			PGA_URW
#define CA_KERN			PGA_KRW
#define CA_VALID(ca)	PGA_VALID(ca)

#define _CATTR_BITSF	/* nothing */
#define _CDEVNR_BITSF	/* nothing */

// captype: on Where a Capability is, CAP_MEM for Memory, CAP_IOPORT for x86 I/O Port
typedef enum cdevnr
{
	CDEV_UNINIT = 0,
	CDEV_MEM,
	CDEV_IOPORT,
} cdevnr_t;

// cap: Capability for some kind of resources in a given region
typedef struct cap
{
	cregion_t	c_reg;
	cattr_t		c_attr	_CATTR_BITSF;
	cdevnr_t	c_dev	_CDEVNR_BITSF;
}
cap_t;

#define c_beg c_reg.beg
#define c_end c_reg.end

#define cap_valid(cap) \
	(region_valid((cap)->c_reg) && \
	CA_VALID((cap)->c_attr))

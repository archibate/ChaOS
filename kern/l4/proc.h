#pragma once


#include <tol/region.h>
#include <l4/vspace.h>
#include <l4/iframe.h>

typedef _region_type(pa_t) pregion_t;
typedef _region_type(va_t) vregion_t, region_t;





typedef enum state
{
	UNINIT = 0,
	ACTIVE,
	ONSEND,
	ONWAIT,
	ONRECV,
}
state_t;



typedef struct tcb
{
	struct tcb *next, *prev;
	state_t state;
	region_t pgreg;
	struct channel *pager;
	vspace_t vs;
	struct pf_info pfi;
}
tcb_t;



#define _QUEUE_NODE			tcb_t
#define _QUEUE_HEAD_STRUCT	tcb_queue
#define _QUEUE_PREF			ch_queue_
#define _QUEUE_HAS_ASSERT	1
#include <tol/queue.h>
typedef struct tcb_queue tcb_queue_t;


typedef struct channel
{
	tcb_t *owner;
	tcb_queue_t queue;
}
channel_t, chan_t;



tcb_t *new_proc(void);
void set_curr_proc(tcb_t *tcb);

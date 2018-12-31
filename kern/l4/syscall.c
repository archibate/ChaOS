#include <l4/vspace.h>
#include <l4/sys/types.h>
#include <l4/sys/chans.h>
#include <tol/region.h>
#include <tol/maxmin.h>
#include <assert.h>
#include <memory.h>
#include <errno.h>
#include <printk.h>
#include <panic.h>

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



#define NMTRS 3



typedef struct tcb
{
	state_t state;
	region_t reg;
	vspace_t vs;
	struct tcb *next, *prev;
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


void block(tcb_t *tcb, state_t state)
{
	tcb->state = state;
}

//tcb_t *_curr_tcb;

void activate(tcb_t *tcb)
{
	tcb->state = ACTIVE;
	//_curr_tcb = tcb; // TOD
}






#define swap(x, y) do { \
	typeof(x) tmp = (x); \
	(x) = (y); \
	(y) = tmp; \
} while (0)


#define TMPADR (KBASE+

void non_aligned_copy(vspace_t *svs, vspace_t *wvs,
		va_t wbeg, va_t sbeg, va_t send, int rev)
{
	size_t len = send - sbeg;
	if (!len)
		return;
	if (rev) {
		swap(wbeg, sbeg);
		swap(wvs, svs);
	}
	pginfo_t pginfo = vs_getmap(svs, wbeg);
	assert(PGI_VALID(pginfo));
	vs_map_s(wvs, KTMPADR, pginfo);
	pginfo = vs_getmap(svs, sbeg);
	assert(PGI_VALID(pginfo));
	vs_map_s(svs, KTMPADR, pginfo);
	memcpy((void*)wbeg, (void*)sbeg, len);
}

//#define HAS_PA_FAST_COPY 1
void page_aligned_copy(vspace_t *svs, vspace_t *wvs,
		pgva_t wbeg, pgva_t sbeg, pgva_t send, int rev)
{
	size_t len = send - sbeg;
	if (!len)
		return;
	if (rev) {
		swap(wbeg, sbeg);
		swap(wvs, svs);
	}
#if HAS_PA_FAST_COPY
	for (; len > 0; len -= PGSIZE)
	{
		pginfo_t pginfo = vs_getmap(svs, sbeg);
		assert(PGI_VALID(pginfo));
		vs_map_s(wvs, wbeg, pginfo);
	}
#else
	memcpy((void*)wbeg, (void*)sbeg, len);
#endif
}



void copy_region_s2w(vspace_t *svs, vspace_t *wvs,
		vregion_t *s, vregion_t *w, int rev)
{
	va_t s_beg = PGUP(s->beg);
	va_t s_end = PGDN(s->end);
	va_t w_beg = PGUP(w->beg);
	va_t wb_beg = w_beg + (s_beg - s->beg);
	va_t w_end = MIN(PGDN(w->end), PGDN(wb_beg + region_size(s)));
	va_t wb_end = w_end - (s_end - s->end);

	non_aligned_copy(wb_beg, s->beg, s_beg, rev);
	page_aligned_copy(svs, wvs, w_beg, s_beg, s_end, rev);
	non_aligned_copy(w_end, s_end, s->end, rev);

	w->beg = wb_beg;
	w->end = wb_end;
}

























#define ipc_copy_s2w(s, w) copy_region_s2w(&(s)->vs, &(w)->vs, &(s)->reg, &(w)->reg, 0)
#define ipc_copy_w2r(w, r) copy_region_s2w(&(w)->vs, &(r)->vs, &(w)->reg, &(r)->reg, 1)






void new_tcb(void)
{
}








int l4_call(tcb_t *sender, chan_t *w_channel, int noblock)
{
	tcb_t *waiter = w_channel->owner;
	tcb_queue_t *wait_queue = &w_channel->queue;

	if (waiter)// && waiter->state == ONWAIT)
	{
		assert(waiter->state == ONWAIT);
		ipc_copy_s2w(sender, waiter);
		block(sender, ONRECV);
		activate(waiter);
	}
	else
	{
		if (noblock)
			return -EWBLOCK;
		block(sender, ONSEND);
		ch_queue_append(wait_queue, sender);
	}

	return 0;
}


int l4_softirq(chan_t *w_channel)
{
	tcb_t hwtcb;
	l4_call(&hwtcb, w_channel, 1);
}


int l4_wait(tcb_t *waiter, chan_t *w_channel)
{
	if (w_channel->owner)
		return -EOWCHAN;
	else
		w_channel->owner = waiter;

	tcb_queue_t *wait_queue = &w_channel->queue;

	if (ch_queue_empty(wait_queue))
	{
		block(waiter, ONWAIT);
	}
	else
	{
		tcb_t *sender = ch_queue_pop(wait_queue);
		assert(sender->state == ONSEND);
		ipc_copy_s2w(sender, waiter);
		block(sender, ONRECV);
	}

	return 0;
}


int l4_reply(tcb_t *waiter, chan_t *w_channel, tcb_t *recver)
{
	if (w_channel->owner != waiter)
		return -EOWCHAN;
	w_channel->owner = 0;

	if (recver->state != ONRECV)
		return -ENCONN;

	ipc_copy_w2r(waiter, recver);
	activate(recver);
	return 0;
}


int l4_reply_wait(tcb_t *waiter, chan_t *w_channel, tcb_t *recver)
{
	int ret = l4_reply(waiter, w_channel, recver);

	if (ret < 0)
		return ret;
	else
		return l4_wait(waiter, w_channel);
}












































tcb_t procs[MAX_PID];
channel_t channels[MAX_CHID];



#define CH(chid)	(&channels[chid])
#define P(pid)		(&procs[pid])
#define PCURR		P(0)








#include <l4/syscall.h>

void system_call(sysnr_t nr, long *a0, long *a1, long *a2, long *a3)
{
	//panic("l4Syscall(nr=%d,%ld,%ld,%ld,%ld)", nr, *a0, *a1, *a2, *a3);
	PCURR->reg.beg = *a1;
	PCURR->reg.end = *a2;
	if (!region_valid(&PCURR->reg)) {
		printk("L4: Invalid region %p->%p", PCURR->reg.beg, PCURR->reg.end);
		*a0 = -EINVAL;
		goto out;
	}

	switch (nr) {
	case L4SYS_CALL:
		printk("l4Call(pid=%d)", *a0);
		*a0 = l4_call(PCURR, CH(*a0), 0);
		break;
	case L4SYS_CALLNB:
		printk("l4CallNB(pid=%d)", *a0);
		*a0 = l4_call(PCURR, CH(*a0), 1);
		break;
	case L4SYS_WAIT:
		printk("l4Wait()");
		*a0 = l4_wait(PCURR, CH(*a0));
		*a1 = PCURR->reg.beg;
		*a2 = PCURR->reg.end;
		break;
	case L4SYS_REPLY:
		printk("l4Reply(chid=%d, pid=%d)", *a0, *a3);
		*a0 = l4_reply(PCURR, CH(*a0), P(*a3));
		break;
	case L4SYS_REPLY_WAIT:
		printk("l4ReplyWait()");
		*a0 = l4_reply_wait(PCURR, CH(*a0), P(*a3));
		*a1 = PCURR->reg.beg;
		*a2 = PCURR->reg.end;
		break;
	default:
		printk("l4NOSYS(nr=%d,%ld,%ld,%ld,%ld)", nr, *a0, *a1, *a2, *a3);
		*a0 = -ENOSYS;
		assert_info(0, "ENOSYS");
		break;
	};

out:
	printk("L4 returning %d", *a0);
}

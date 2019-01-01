#include <l4/proc.h>
#include <l4/sys/types.h>
#include <l4/sys/chans.h>
#include <tol/maxmin.h>
#include <l4/iframe.h>
#include <assert.h>
#include <memory.h>
#include <errno.h>
#include <printk.h>
#include <panic.h>







tcb_t procs[MAX_PID];
channel_t channels[MAX_CHID];



#define CH(chid)	(&channels[chid])
#define P(pid)		(&procs[pid])
#define PCURR		_pcurr
tcb_t *_pcurr = 0, *_curr_next = 0;


void block(tcb_t *tcb, state_t state)
{
	tcb->state = state;
}

void activate(tcb_t *tcb)
{
	tcb->state = ACTIVE;
	_curr_next = tcb;
}

tcb_t *select_next(void)
{
	int i;
	for (i = 0; i < MAX_PID; i++) {
		//printk("select_next: checking pid=%d", i);
		if (procs[i].state == ACTIVE) {
			printk("select_next: selected pid=%d proc=%p", i, &procs[i]);
			return &procs[i];
		}
	}
	panic("select_next: no runnable task!");
}

void schedule(void)
{
	printk("schedule: _curr_next=%p", _curr_next);
	/*static int i;
	if (i++)
		panic("schedule");*/

	if (!_curr_next) {
		if (_pcurr->state == ACTIVE)
			return;

		_curr_next = select_next();
		assert(_curr_next);
	}
	printk("schedule: set_curr_proc from %p to %p", _pcurr, _curr_next);
	set_curr_proc(_curr_next);
	_curr_next = 0;
}






#if 0 // {{{
#define swap(x, y) do { \
	typeof(x) tmp = (x); \
	(x) = (y); \
	(y) = tmp; \
} while (0)


void non_aligned_copy(vspace_t *svs, vspace_t *wvs,
		va_t wbeg, va_t sbeg, va_t send, int rev)
{
#if 0 // {{{
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
#endif // }}}
}

//#define HAS_PA_FAST_COPY 1
void page_aligned_copy(vspace_t *svs, vspace_t *wvs,
		pgva_t wbeg, pgva_t sbeg, pgva_t send, int rev)
{
#if 0 // {{{
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
#endif // }}}
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
#endif // }}}



















#if 0
void ipc_short_copy(tcb_t *s, tcb_t *w)
{
	va_t sbeg = PGDN(s->reg.beg);
	va_t send = PGUP(s->reg.end);
	va_t va;
	for (va = sbeg; va < send; va += PGSIZE)
	{
		pginfo_t pginfo = vs_getmap(s->vs, va);
		pa_t pa = PGI_PADDR(pginfo);
		vs_map(w->vs, pa);
	}
}
#endif












#if 1
#define ipc_copy_s2w(s, w) //ipc_short_copy(s, w)//copy_region_s2w(&(s)->vs, &(w)->vs, &(s)->reg, &(w)->reg, 0)
#define ipc_copy_w2r(w, r) //ipc_short_copy(w, r)//copy_region_s2w(&(w)->vs, &(r)->vs, &(w)->reg, &(r)->reg, 1)
#endif






void set_curr_proc(tcb_t *tcb)
{
	_pcurr = tcb;
	vspace_use(&tcb->vs);
}

tcb_t *new_proc(void)
{
	static int proc_max = 0;
	tcb_t *proc = P(proc_max++);
	memset(proc, 0, sizeof(*proc));
	return proc;
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
		printk(KL_DEBUG "l4_call: activate waiter");
		activate(waiter);
	}
	else
	{
		if (noblock) {
			printk(KL_DEBUG "l4_call: EWBLOCK");
			return -EWBLOCK;
		}
		printk(KL_DEBUG "l4_call: block sender");
		block(sender, ONSEND);
		ch_queue_append(wait_queue, sender);
	}

	return 0;
}



void l4_page_fault(tcb_t *proc, va_t addr, uint errcd)
{
	if (proc->pager && region_valid(&proc->pgreg) && region_in(&proc->pgreg, addr))
	{
		proc->pfi.offset = addr - proc->pgreg.beg;
		proc->pfi.errcd = errcd;
		printk("l4_page_fault: va=%p pager=%p region matched", addr, proc->pager);
		int r = l4_call(proc, proc->pager, 0);
		if (r)
			panic("l4_page_fault: l4_call to pager returns %d", r);
		printk("l4_page_fault: returning");
		return;
	}
	panic("l4_page_fault(vaddr=%p, errcd=%d) with no soultion", addr, errcd);
}

void on_page_fault(va_t addr, uint errcd)
{
	printk("on_page_fault(vaddr=%p, errcd=%d)", addr, errcd);
	l4_page_fault(PCURR, addr, errcd);
}

#include <asm/iframe.h>
#include <x86/cregs.h>
void do_page_fault(struct iframe *iframe)
{
	va_t addr = getcr2();
	uint errcd = iframe->errcd;

	if ((iframe->cs & 3) == 0)
		panic("in-kernel page fault at vaddr=%p, errcd=%d", addr, errcd);

	if (errcd & 1)
		panic("user access violatled at vaddr=%p, errcd=%d", addr, errcd);

	on_page_fault(addr, errcd);
	schedule();
}


int l4_softirq(chan_t *w_channel)
{
	tcb_t hwtcb;
	return l4_call(&hwtcb, w_channel, 1);
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




















































#include <l4/syscall.h>

void system_call(sysnr_t nr, long *a0, long *a1, long *a2, long *a3)
{
	//panic("l4Syscall(nr=%d,%ld,%ld,%ld,%ld)", nr, *a0, *a1, *a2, *a3);

	switch (nr) {
	case L4SYS_SET_PAGER:
		printk("l4SetPager(chid=%d)", *a0);
		PCURR->pgreg = make_region(*a1, *a2);
		if (!region_valid(&PCURR->pgreg)) {
			printk("L4: Invalid region %p->%p", PCURR->pgreg.beg, PCURR->pgreg.end);
			*a0 = -EINVAL;
			goto out;
		}
		PCURR->pager = *a0 == -1 ? 0 : CH(*a0);
		*a0 = 0;
		break;
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
		break;
	case L4SYS_REPLY:
		printk("l4Reply(chid=%d, pid=%d, pgva=%p)", *a0, *a3, *a1);
		va_t retpgva = PGDN(*a1);
		pginfo_t pginfo = vs_getmap(&PCURR->vs, retpgva);
		if (!PGI_VALID(pginfo)) {
			*a0 = -EFAULT;
			printk("L4: Fault address %p", retpgva);
			goto out;
		}
		tcb_t *rcvr = P(*a3);
		vs_map(&rcvr->vs, rcvr->pgreg.beg + rcvr->pfi.offset, pginfo);
		*a0 = l4_reply(PCURR, CH(*a0), rcvr);
		break;
#if 0
	case L4SYS_REPLY_WAIT:
		printk("l4ReplyWait()");
		*a0 = l4_reply_wait(PCURR, CH(*a0), P(*a3));
		*a1 = PCURR->pgreg.beg;
		*a2 = PCURR->pgreg.end;
		break;
#endif
	default:
		printk("l4NOSYS(nr=%d,%ld,%ld,%ld,%ld)", nr, *a0, *a1, *a2, *a3);
		*a0 = -ENOSYS;
		assert_info(0, "ENOSYS");
		break;
	};

out:
	printk("L4 returning %d", *a0);
	schedule();
}

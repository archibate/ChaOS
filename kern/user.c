#include <mm/pmm.h>
#include <mm/umem.h>
#include <mm/page.h>
#include <l4/proc.h>
#include <mm/kbase.h>
#include <l4/vspace.h>
#include <asm/touser.h>
#include <tol/maxmin.h>
#include <printk.h>
#include <conio.h>

static void vs_maps(vspace_t *vs, va_t vstart, size_t size, pginfo_t pgi0)
{
	va_t va;
	pginfo_t pgi = pgi0;
	for (va = vstart; va < vstart + size; va += PGSIZE)
	{
		vs_map(vs, va, pgi);
		pgi += PGSIZE;
	}
}

static void vs_newzpgs(vspace_t *vs, va_t vstart, size_t size, pgattr_t pgattr)
{
	va_t va;
	for (va = vstart; va < vstart + size; va += PGSIZE)
	{
		pa_t pa = zalloc_ppage();
		vs_map(vs, va, PGINFO(pa, pgattr));
	}
}

void arch_init_if_regs(struct iframe *ifr, ulong pc, ulong sp)
{
	ifr->pc = pc;
	ifr->sp = sp;
	ifr->cs = SEG_UCODE;
	ifr->ds = SEG_UDATA;
	ifr->es = SEG_UDATA;
	ifr->ss = SEG_UDATA;
}

void _make_user_vspace(vspace_t *vs, const char *name, int stkpgs,
		void *pbeg, void *pend, int fsiz, int zsiz)
{
	pa_t beg = PGDN(KV2P((va_t)pbeg));
	pa_t end = PGUP(KV2P((va_t)pend));

	fsiz = PGUP(end - beg);
	zsiz = PGUP(zsiz);

	printk(KL_INFO "%s: fsiz=%#lx, zsiz=%#lx", name, fsiz, zsiz);

	vspace_newinit(vs);

	pa_t ppsp = zalloc_ppage();
	vs_map(vs, PGDN(KSTKTOP), PGINFO(ppsp, PGA_URO));
	((struct iframe*)KSTKTOP)[-1];
	struct iframe *psp = (void*)KP2V(ppsp);
	arch_init_if_regs(psp, UBASE, USTKTOP - 16);

	int stksz = PGSIZE * stkpgs;
	vs_maps(vs, UBASE, fsiz, PGINFO(beg, PGA_URW));
	vs_newzpgs(vs, UBASE + fsiz, zsiz, PGA_URW);
	vs_maps(vs, USRVRAM, PGUP(80 * 25 * 2), PGINFO(0xb8000, PGA_URW));
	vs_newzpgs(vs, USTKTOP - stksz, stksz, PGA_URW);
}
#define make_user_vspace(vs, name, stkpgs) do { \
	extern char name##_beg[], name##_end[]; \
	extern int name##_fsiz, name##_zsiz; \
	_make_user_vspace(vs, #name, stkpgs, name##_beg, name##_end, name##_fsiz, name##_zsiz); \
} while (0)

#define make_user_proc(name, stkpgs) \
	tcb_t *name = new_proc(); \
	make_user_vspace(&name->vs, name, stkpgs); \

void init_user(void)
{
	make_user_proc(sigma0, 10);
	make_user_proc(roottask, 10);

	cputs("Transfering to RootTask...");
	set_curr_proc(roottask);
	roottask->state = sigma0->state = ACTIVE;
	transfer_to_user(UBASE, USTKTOP - 16);
}

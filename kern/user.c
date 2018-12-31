#include <mm/pmm.h>
#include <mm/umem.h>
#include <mm/page.h>
#include <mm/kbase.h>
#include <l4/vspace.h>
#include <asm/touser.h>
#include <tol/maxmin.h>
#include <sigma0.h>
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

void init_user(void)
{
	extern char sigma0_beg[], sigma0_end[];
	pa_t beg = PGDN(KV2P((va_t)&sigma0_beg));
	pa_t end = PGUP(KV2P((va_t)&sigma0_end));

	size_t fsiz = PGUP(end - beg);
	size_t zsiz = PGUP(S0ZSIZ);

	printk(KL_INFO "sigma0: fsiz=%#lx, zsiz=%#lx", fsiz, zsiz);

	vspace_t vs;
	vspace_newinit(&vs);

	int stksz = 10 * PGSIZE;
	vs_maps(&vs, UBASE, fsiz, PGINFO(beg, PGA_URW));
	vs_newzpgs(&vs, UBASE + fsiz, zsiz, PGA_URW);
	vs_maps(&vs, USRVRAM, PGUP(80 * 25 * 2), PGINFO(0xb8000, PGA_URW));
	vs_newzpgs(&vs, USTKTOP - stksz, stksz, PGA_URW);
	
	vspace_use(&vs);
	
	cputs("Transfering to Sigma0...");
	transfer_to_user(UBASE, USTKTOP - 16);
}

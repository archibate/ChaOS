#include <asm/touser.h>
#include <asm/iframe.h>
#include <asm/setksp.h>
#include <x86/eflags.h>
#include <x86/gdt.h>
#include <ccutils.h>
#include <printk.h>

void transfer_to_user(ulong pc, ulong sp)
{
	static struct iframe ifr;
	ifr.ss = SEG_UDATA;
	ifr.cs = SEG_UCODE;
	ifr.es = ifr.ds = ifr.ss;
	ifr.pc = pc;
	ifr.sp = sp;
	ifr.eflags = FL_1F;
	
	*(volatile int*)pc;
	printk("transter_to_user...");
	
	ulong ksp;
	asm volatile ("mov %%esp, %0" : "=r" (ksp) :);
	set_ksp(ksp);
	
	asm volatile ("mov %0, %%esp\njmp _intreturn" :: "r" (&ifr));
	UNREACHABLE();
}

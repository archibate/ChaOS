D=../
ALL=kernel.bin
LIBS=gcc c con
include $Dbeg.mak
OBJS=x86/entry.o x86/gdt.o x86/idt.o x86/tss.o x86/memtest.o \
	 x86/intrents.o x86/hwintr.o x86/excpvecs.o x86/irqvecs.o \
	 main.o initrd.o timer.o user.o printk.o assert.o \
	 mm/minfo.o mm/bootvm.o mm/uvm.o mm/pmm.o mm/vmm.o \
	 drv/pic.o drv/pit.o drv/vga.o asm/touser.o \
	 l4/syscall.o
include $Ddep.mak

kernel.bin: kernel.sys
	$(OBJCOPY) -O binary -R .note -R .comment $< $@

kernel.sys: kernel.ld.i $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -T kernel.ld.i -o $@ $(OBJS) $(LIBS:%=-l%)

initrd.o: $Dsigma0/sigma0.bin

include $Dend.mak
include .dep

D=../
ALL=kernel.bin
include $Dbeg.mak
OBJS=x86/entry.o main.o x86/gdt.o x86/idt.o x86/tss.o x86/memtest.o \
	 x86/intrents.o x86/hwintr.o x86/excpvecs.o x86/irqvecs.o \
	 drv/pic.o drv/pit.o drv/vga.o timer.o user.o printk.o assert.o \
	 mm/minfo.o mm/bootvm.o mm/uvm.o mm/pmm.o mm/vmm.o initrd.o
OBJS+=$Dlibcon/libcon.a $Dlibc/libc.a \
	  $(if $(WIN),$Dz_tools/mingw/libgcc.a,$(shell $(CC) -print-libgc-file-name))

kernel.bin: kernel.sys
	$(OBJCOPY) -O binary $< $@

kernel.sys: kernel.ld $(OBJS)
	$(LD) $(LDFLAGS) -T kernel.ld -o $@ $(OBJS)

include $Dend.mak

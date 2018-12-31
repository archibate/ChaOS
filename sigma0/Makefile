D=../
ALL=sigma0.bin
LIBS=gcc con c
include $Dbeg.mak
OBJS=x86/entry.o main.o drv/vga.o
DEPISRC+=sigma0.ld.i
include $Ddep.mak

sigma0.bin: sigma0.sys
	$(OBJCOPY) -O binary $< $@

sigma0.sys: sigma0.ld $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -T sigma0.ld -o $@ $(OBJS) $(LIBS:%=-l%)

include $Dend.mak
-include .dep

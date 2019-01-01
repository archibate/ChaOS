D=../
ALL=roottask.bin
LIBS=gcc con c
include $Dbeg.mak
OBJS=x86/entry.o main.o drv/vga.o
DEPISRC+=roottask.ld.i
include $Ddep.mak

roottask.bin: roottask.sys
	$(OBJCOPY) -O binary $< $@

roottask.sys: roottask.ld $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -T roottask.ld -o $@ $(OBJS) $(LIBS:%=-l%)

include $Dend.mak
-include .dep

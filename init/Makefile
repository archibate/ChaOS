D=../
ALL=init.bin
include $Dbeg.mak
OBJS=x86/entry.o
OBJS+=$Dlibcon/libcon.a $Dlibc/libc.a \
	  $(if $(WIN),$Dz_tools/mingw/libgcc.a,$(shell $(CC) -print-libgc-file-name))

init.bin: init.sys
	$(OBJCOPY) -O binary $< $@

init.sys: init.ld $(OBJS)
	$(LD) $(LDFLAGS) -T init.ld -o $@ $(OBJS)

include $Dend.mak

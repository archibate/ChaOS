D=../
ALL=sigma0.bin
LIBS=gcc c con
include $Dbeg.mak
OBJS=x86/entry.o

sigma0.bin: sigma0.sys
	$(OBJCOPY) -O binary $< $@

sigma0.sys: sigma0.ld $(OBJS)
	$(LD) $(LDFLAGS) -T sigma0.ld -o $@ $(OBJS) $(LIBS:%=-l%)

include $Dend.mak

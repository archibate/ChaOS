D=./
ALL=chaos.img
include $Dbeg.mak
DIRS=boot sigma0 kern libc libcon

.PHONY: run
run: chaos.img
ifdef WINQEMU
	cp $< z_tools/qemu/fdimage0.bin
	make -C z_tools/qemu
else
	qemu-system-x86_64 -m 32 -boot a -fda $<
endif

.PHONY: bochsrun
bochsrun: chaos.img
	bochs -qf bochsrc.bxrc

.PHONY: bochsdbg
bochsdbg: chaos.img
	bochsdbg -qf bochsrc.bxrc

chaos.img: boot/boothead.bin kern/kernel.bin
ifdef WIN
	copy /b boot\boothead.bin+kern\kernel.bin $@
else
	cat $^ > $@
endif

#kern/kernel.bin: libc/libc.a libcon/libcon.a init/init.bin

.PHONY: $(foreach x, $(DIRS), $x/ $x/*)
$(foreach x, $(DIRS), $x/%):
	make -C $(@D) $(@F)

include $Dend.mak

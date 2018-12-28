D=./
ALL=chaos.img
include $Dbeg.mak
DIRS=boot kern libc libcon

.PHONY: run
run: chaos.img
	cp $< z_tools/qemu/fdimage0.bin
	make -C z_tools/qemu

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

#kern/kernel.bin: libc/libc.a libvgacon/libcon.a

.PHONY: $(foreach x, $(DIRS), $x/ $x/*)
$(foreach x, $(DIRS), $x/%):
	make -C $(@D) $(@F)

include $Dend.mak

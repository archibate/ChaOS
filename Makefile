D=./
ALL=chaos.img
include $Dbeg.mak
DIRS=libgcc libc libcon sigma0 roottask kern boot

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

chaos.img: $(DIRS)
ifdef WIN
	copy /b boot\boothead.bin+kern\kernel.bin $@
else
	rm -rf `readlink $@`
	rm -rf $@
	ln -s /tmp/4300 $@
	dd if=/dev/zero of=$@ count=1440 bs=1024
	cat boot/boothead.bin kern/kernel.bin | dd of=$@ conv=notrunc count=1440 bs=1024
endif

.PHONY: $(DIRS)
$(DIRS):
	make -C $@

clean:
	for x in $(DIRS); do make -C $$x $@; done

#include $Dend.mak

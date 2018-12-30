D=../
ALL=libgcc.a
include $Dbeg.mak
GCC_LIB=$(shell $(CC) $(CFLAGS) -print-libgcc-file-name)

libgcc.a: $(GCC_LIB)
	cp $< $@

include $Dend.mak

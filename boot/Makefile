D=../
ALL=boothead.bin
include $Dbeg.mak

boothead.bin: boot.bin head.bin
ifdef WIN
	copy /b boot.bin+head.bin $@
else
	cat $^ > $@
endif

include $Dend.mak
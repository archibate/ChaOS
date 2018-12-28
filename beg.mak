#WIN=1
WINQEMU=1

.PHONY: all
all: $(ALL)

# tools & flags:

ASM=nasm
AS=as
CC=gcc
CC1=cc1
OBJCOPY=objcopy

OPTIMIZE=0
MODES+=32 arch=i386 soft-float
FUNCTIONS+=no-common no-exceptions no-non-call-exceptions freestanding no-builtin
WARNINGS+=all no-unused-function implicit-function-declaration
INCPATH+=. $Dlibc $Dlibcon $Dinclude
LIBPATH+=$Dlibc

ifndef WIN
FUNCTIONS+=no-stack-protector
WARNINGS+=no-error=unused-variable no-error=unused-but-set-variable
else
DEFINES+=_MINGW=1
endif

CCFLAGS+=-nostdinc
CCFLAGS+=$(OPTIMIZE:%=-O%) $(MODES:%=-m%) \
		$(FUNCTIONS:%=-f%) $(WARNINGS:%=-W%) \
		$(DEFINES:%=-D%) $(INCPATH:%=-I%)
ASMFLAGS+=$(INCPATH:%=-I%/)
LDFLAGS+=-s -static -nostdlib
LDFLAGS+=$(LIBPATH:%=-L%) $(LIBS:%=-l%)
CFLAGS=$(CCFLAGS) $(LDFLAGS)

# compiling rules:

%.bin: %.asm
	$(ASM) $(ASMFLAGS) -f bin -o $@ $<

%.o: %.asm
	$(ASM) $(ASMFLAGS) -f elf -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.s: %.c
	$(CC1) -quiet $(CCFLAGS) -o .$@ $<
	$(OBJCOPY) -O elf32-i386 .$@ $@

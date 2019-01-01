#WIN=1
#WINQEMU=1

.PHONY: all
all: $(ALL)

# tools & flags:

ASM=nasm
AS=as
CC=gcc
CC1=cc1
OBJCOPY=objcopy

OPTIMIZE=0
DEFINES+=__WORDSIZE__=4
MODES+=32 arch=i386 soft-float
FUNCTIONS+=no-common no-exceptions no-non-call-exceptions freestanding no-builtin
WARNINGS+=all no-unused-function implicit-function-declaration no-main no-format
INCPATH+=. $Dlibgcc $Dlibc $Dlibcon $Dinclude
LIBPATH+=$Dlibgcc $Dlibc $Dlibcon

# These options may not be recognized by MinGW gcc:
FUNCTIONS+=no-stack-protector
WARNINGS+=no-error=unused-variable no-error=unused-but-set-variable error=incompatible-pointer-types

#ifndef WIN
#FUNCTIONS+=no-stack-protector
#WARNINGS+=no-error=unused-variable no-error=unused-but-set-variable
#else
#DEFINES+=_MINGW=1
#endif

CFLAGS+=-nostdinc
CFLAGS+=$(OPTIMIZE:%=-O%) $(MODES:%=-m%) \
		$(FUNCTIONS:%=-f%) $(WARNINGS:%=-W%) \
		$(DEFINES:%=-D%) $(INCPATH:%=-I%)
ASMFLAGS+=$(INCPATH:%=-I%/)
LDFLAGS+=-static -nostdlib
LDFLAGS+=$(LIBPATH:%=-L%)

# compiling rules:

%.bin: %.asm
	$(ASM) $(ASMFLAGS) -f bin -o $@ $<

%.o: %.asm
	$(ASM) $(ASMFLAGS) -f elf -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.i: %
	$(CC) $(CFLAGS) -xc -D_GPCPP_=1 -E -P -o $@ $<

%.o: %.S
	$(CC) $(CFLAGS) -D__ASSEMBLER__=1 -D_GPCPP_=1 -c -o $@ $<

%.d: %.S
	$(CC) $(CFLAGS) -D__ASSEMBLER__=1 -D_GPCPP_=1 -M -o $@ $<

%.d: %.asm
	$(ASM) $(ASMFLAGS) -M -o $*.o $< > $@

%.d: %.c
	$(CC) $(CFLAGS) -M -o $@ $<

%.d: %
	$(CC) $(CFLAGS) -xc -D_GPCPP_=1 -M -MT $*.i -P -o $@ $<

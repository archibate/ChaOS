D=../
ALL=libc.a
include $Dbeg.mak
C_SRCS=$(wildcard *.c)
S_SRCS=$(wildcard *.asm)
OBJS=$(C_SRCS:%.c=%.o) $(S_SRCS:%.asm=%.o)

libc.a: $(OBJS)
	ar cqs $@ $^

include $Dend.mak

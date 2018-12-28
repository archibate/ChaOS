#pragma once

#include <ccutils.h>

#define cli()       asm volatile ("cli")
#define sti()       asm volatile ("sti")
#define hlt()       asm volatile ("hlt")
#define stihlt()    asm volatile ("sti;hlt")
#define stihltcli() asm volatile ("sti;hlt;cli")
#define sticli()    asm volatile ("sti;cli")
#define clihlt()    do { asm volatile ("cli;hlt"); UNREACHABLE(); } while (1)

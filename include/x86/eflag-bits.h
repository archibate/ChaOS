#pragma once

// http://www.cnblogs.com/shenlian/archive/2011/05/22/2053857.html
// x86 eflags bits:
#define FL_CF      (1<<0)		// S: Carry
#define FL_1F      (1<<1)		// -: Always be 1
#define FL_PF      (1<<2)		// S: Parity
#define FL_AF      (1<<4)		// S: Auxiliary Carry
#define FL_ZF      (1<<6)		// S: Zero
#define FL_SF      (1<<7)		// S: Sign
#define FL_YF      (1<<8)		// X: Trap
#define FL_IF      (1<<9)		// X: Interrupt Enable
#define FL_DF      (1<<10)		// C: Direction
#define FL_OF      (1<<11)		// S: Overflow
#define FL_IOPL(x) ((x)<<12)	// X: I/O Privilege Level
#define FL_NT      (1<<14)		// X: Nested Task
#define FL_RF      (1<<16)		// X: Resume Flag
#define FL_AC      (1<<17)		// X: Alignment Check
#define FL_VM      (1<<18)		// X: Virtual-8086 Mode
#define FL_VIF     (1<<19)		// X: Virtual Interrupt Flag
#define FL_VIP     (1<<20)		// X: Virtual Interrupt Pending
#define FL_ID      (1<<21)		// X: ID Flag
// S := Status Flag
// C := Control Flag
// X := System Flag
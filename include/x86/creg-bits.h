#pragma once

// http://blog.sina.com.cn/s/blog_85998e38010122wq.html

// CR0 bits:
#define CR0_PG  (1<<31)	// Paging
#define CR0_CD  (1<<30)	// Cache Disable
#define CR0_NW  (1<<29)	// No Writethrough
#define CR0_AM  (1<<18)	// Alignment Mask
#define CR0_WP  (1<<16)	// Write Protect
#define CR0_NE  (1<<5)	// Numeric Error
#define CR0_ET  (1<<4)	// Extension Type (Readonly)
#define CR0_TS  (1<<3)	// Task Switched
#define CR0_EM  (1<<2)	// Math Emulation
#define CR0_MP  (1<<1)	// Monitor Coprocessor
#define CR0_PE  (1<<0)	// Protect Enabled

// CR3 bits:
#define CR3_PCD (1<<4)	// Page Cache Disable
#define CR3_PNW (1<<3)	// Page No Writethrough

// CR4 bits:
#define CR4_PCE (1<<8)	// Performance Monitoring Counter Enable
#define CR4_PGE (1<<7)	// Page-Global Enable
#define CR4_MCE (1<<6)	// Machine Check Enable
#define CR4_PAE (1<<5)	// Physical-Address Extension
#define CR4_PSE (1<<4)	// Physical-Size Extensions
#define CR4_DE  (1<<3)	// Debugging Extensions
#define CR4_TSD (1<<2)	// Time Stamp Disable
#define CR4_PVI (1<<1)	// Protected-Mode Virtual Interrupts
#define CR4_VME (1<<0)	// Virtual-8086 Mode Extensions

#define CR4_OSXSAVE		(1<<18)	// XSAVE and Processor Extended States Enable
#define CR4_OSXMMEXCP	(1<<10)	// Operating System Unmasked Exception Support
#define CR4_OSFXSR		(1<<9)	// Operating System FXSAVE/FXRSTOR Support

// EFER bits:
#define EFER_FFXSR	(1<<14)		// Fast FXSAVE/FXRSTOR
#define EFER_LMSLE	(1<<13)		// Long Mode Segment Limit Enable
#define EFER_SVME	(1<<12)		// Secure Virtual Machine Enable
#define EFER_NXE	(1<<11)		// No-Execute Enable
#define EFER_LMA	(1<<10)		// Long Mode Active (Readonly)
#define EFER_LME	(1<<8)		// Long Mode Enable
#define EFER_SCE	(1<<0)		// System Call Extensions

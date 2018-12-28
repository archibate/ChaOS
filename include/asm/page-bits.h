#pragma once

#define PTE_P   0x1     // Present
#define PTE_W   0x2     // Read / Write
#define PTE_U   0x4     // User / Kern
#define PTE_K   0x0     // User / Kern
#define PTE_PWT 0x8     // Write through
#define PTE_PCD 0x10    // Cache disable
#define PTE_A   0x20    // Accessed
#define PTE_D   0x40    // Dirty
#define PTE_PAT 0x80    // Page Attribute Table (unused)
#define PTE_G   0x100   // Global (unused)

#define PDE_P   0x1     // Present
#define PDE_W   0x2     // Read / Write
#define PDE_U   0x4     // User / Kern
#define PDE_K   0x0     // User / Kern
#define PDE_PWT 0x8     // Write through
#define PDE_PCD 0x10    // Cache disable
#define PDE_A   0x20    // Accessed
#define PDE_PSE 0x80    // Page Size Extension (unused)
#define PDE_G   0x100   // Global (unused)

#define PGWID   12		// Page Offset Width
#define PTWID   10		// Page Table Index Width
#define PDWID   10		// Page Directory Index Width
#define VAWID   32		// Virtual Address Width (Sum of above)

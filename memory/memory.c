#include "memory.h"
#include <stdint.h>

// this page directory for the kernel, it has 1024 4 byte entry.
extern uint32_t* initial_page_dir;
extern uint32_t* kernel_end;

// uint32_t* page_frames[1024];

static inline void _invlpg(unsigned long addr) {
   asm volatile("invlpg (%0)" ::"r" (addr) : "memory");
}

void initMemory() {
    uint32_t* pgd = (uint32_t*)&initial_page_dir;
    // invalidate the lower half
    pgd[0] = 0;
    _invlpg(0);
    // after this point, we cannot address anything in the 1st 4 MB of the address space.

    // pgd[768] is the first 4 MB of our kernel.
    // enabling the next page
    // pgd[768] = pgd[768] | 0xf0400000;
    pgd[769] = 0xf0400083;
    uint32_t max_limit = 0x1fb80 * 1024;
    pgd[770] = ((0x00C00000 )) | 0x83;
}
#include "memory.h"
#include <stdint.h>
#include "../stdlib/stdio.h"

// this page directory for the kernel, it has 1024 4 byte entry.
extern uint32_t initial_page_dir;
extern uint32_t kernel_end;

static uint32_t physicalAddrStart;
static uint32_t physicalAddrEnd;

static inline void _invlpg(unsigned long addr) {
   asm volatile("invlpg (%0)" ::"r" (addr) : "memory");
}


/**
 * Input arguments are the physical address starting and the length,
 * this can be obtained from the multiboot information 
 */
void initMemory(uint32_t startingAddr, uint32_t length) {
    uint32_t* pgd = (uint32_t*)&initial_page_dir;
    // set the initial page to 0, this is only to be used by the user space
    pgd[0] = 0;
    _invlpg(0);
    
    physicalAddrStart = startingAddr + ((uint32_t)&kernel_end - 0xC0000000);
    physicalAddrEnd = physicalAddrStart + length; 
    printf("%x - %x\n", physicalAddrStart, physicalAddrEnd);
}
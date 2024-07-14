#ifndef MEMORY_H
#define MEMORY_H
#include<stdint.h>

/**
 * @param startingAddr: start of the physical address
 * @param length: length of the phycal address space available
 */
void initMemory(uint32_t startingAddr, uint32_t length);

#endif
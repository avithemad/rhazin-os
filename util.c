#include "util.h"
void outPortB(uint16_t port, uint8_t value) {
    asm volatile ("outb %1, %0" : : "dN" (port),  "a" (value));
    // uint16_t p1 = 0x80;
    // uint8_t v1 = 0x0;
    // asm volatile ("outb %1, %0" : : "dN" (p1),  "a" (v1));
}

void memset(void *dest, char val, uint32_t count){
    char *temp = (char*) dest;
    for (; count != 0; count --){
        *temp++ = val;
    }

}
char inPortB(uint16_t port) {
    char rv;
    asm volatile("inb %1, %0": "=a"(rv):"dN"(port));
    return rv;
}
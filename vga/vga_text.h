#ifndef VGA_H
#define VGA_H
#include<stdint.h>

void init_screen(uint16_t* buffer_address);
void print(const char* string);
void putchar(char c);
#endif
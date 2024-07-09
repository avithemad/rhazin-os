#ifndef VGA_H
#define VGA_H
#include<stdint.h>

void init_screen();
void print(const char* string);
void putchar(char c);
void init_framebuffer(uint32_t* addr);
void draw();
#endif
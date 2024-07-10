#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include<stdint.h>

void init_screen(uint32_t* addr, uint32_t width, uint32_t height);
void print(const char* string);
void putchar(char c);
#endif
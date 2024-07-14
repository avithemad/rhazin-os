#include "vga_text.h"
#include <stdint.h>
#include <stddef.h>
#include "../stdlib/stdio.h"

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

static size_t row, column;
static int8_t color;
static uint16_t* buffer;

static void clear_screen() {
    for (size_t r=0; r < VGA_HEIGHT; r++){
        for (size_t c=0; c < VGA_WIDTH; c++){
            buffer[r*VGA_WIDTH + c] = vga_entry(' ', color);
        }
    }
}

static void putentryat(char c, size_t x, size_t y) {
    buffer[VGA_WIDTH*x + y] = vga_entry(c, color);
}

void init_screen(uint32_t buffer_address) {
    row = 0;
    column = 0;
    color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    buffer = (uint16_t*)(buffer_address + 0xC0000000);
    clear_screen();
}
//TODO: make this shared in standard library
static int strlen(const char* string) {
    int res=0;
    for (; string[res++]!='\0';);
    return res;
}

void putchar(char c) {
    if (c == '\n'){
        column = 0;
        row++;
    } else {
        putentryat(c, row, column);
        column = (column + 1)%VGA_WIDTH;
        if (column == 0) {
            row++;
        }
    }
    if (row == VGA_HEIGHT) {
        row = 0;
        clear_screen(); 
    }
}


void print(const char* string) {
    int size = strlen(string);
    for (int i=0; i<size-1; i++) {
        putchar(string[i]);
    }
}

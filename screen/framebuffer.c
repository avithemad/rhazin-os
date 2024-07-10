#include "framebuffer.h"
#include <stdint.h>
#include "bitmap.h"

static uint32_t height, width;
static uint32_t* buffer;
// curso
static uint8_t cursor_row = 0;
static uint8_t cursor_col = 0;

void init_screen(uint32_t* fb_addr, uint32_t w, uint32_t h) {
    buffer = fb_addr;
    height = h;
    width = w;
    for (int i=0; i<h*w; i++) {
        fb_addr[i] = 0x000ff0;
    }
}

void print(const char* string) {
    for (int i=0; string[i]!='\0'; i++) {
        putchar(string[i]);
    }
}

void putchar(char c) {
    uint32_t pixel_x = cursor_row*CHAR_HEIGHT;
    uint32_t pixel_y = cursor_col*CHAR_WIDTH;
    if (c != '\n') {
        for (int i = 0; i < CHAR_HEIGHT; i++) {
            for (int j=0; j < CHAR_WIDTH; j++) {
                if (lower_case_map[(c-'a')%26][i] & ((1 << CHAR_WIDTH) >> (j))) {
                    buffer[(pixel_x + i)*width + (pixel_y + j)] = 0xFFFFFF;
                }
            }
        }
        cursor_col = (cursor_col + 1)%(width/CHAR_WIDTH);
        if (cursor_col == 0) {
            cursor_row++;
        }
    }
    else {
        cursor_row++;
        cursor_col = 0;
    }
    if (cursor_row == height) {
        cursor_row = 0;
        cursor_col = 0;
    }
}

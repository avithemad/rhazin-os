#ifndef BITMAP_H
#define BITMAP_H
#define CHAR_HEIGHT 16
#define CHAR_WIDTH 8

uint8_t lower_case_map[26][CHAR_HEIGHT] = {
{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x10, 0x18, 0x8, 0x8, 0x18, 0x38, 0x28, 0x38, 0x18, 0x0},
{0x0, 0x0, 0x0, 0x0, 0x20, 0x20, 0x30, 0x38, 0x3c, 0x24, 0x24, 0x24, 0x2c, 0x38, 0x10, 0x0},
{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8, 0x18, 0x30, 0x20, 0x20, 0x20, 0x30, 0x1c, 0x8, 0x0},
{0x0, 0x0, 0x0, 0x0, 0x8, 0x8, 0x18, 0x18, 0x28, 0x28, 0x28, 0x28, 0x28, 0x18, 0x18, 0x0},
{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x18, 0x2c, 0x24, 0x3c, 0x38, 0x20, 0x18, 0x8, 0x0},
{0x0, 0x0, 0x0, 0x0, 0x1c, 0x10, 0x10, 0x3c, 0x38, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x0},
{0x0, 0x0, 0x0, 0x0, 0x0, 0x18, 0x18, 0x28, 0x28, 0x28, 0x28, 0x38, 0x18, 0x8, 0x38, 0x38},
{0x0, 0x0, 0x0, 0x0, 0x20, 0x20, 0x30, 0x38, 0x38, 0x28, 0x28, 0x28, 0x28, 0x2c, 0x0, 0x0},
{0x0, 0x0, 0x0, 0x0, 0x10, 0x10, 0x0, 0x30, 0x30, 0x10, 0x10, 0x10, 0x10, 0x1c, 0x8, 0x0},
{0x0, 0x0, 0x8, 0x8, 0x8, 0x0, 0x18, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x38, 0x18},
{0x0, 0x0, 0x0, 0x0, 0x20, 0x20, 0x20, 0x28, 0x38, 0x38, 0x30, 0x38, 0x38, 0x2c, 0x0, 0x0},
{0x0, 0x0, 0x0, 0x0, 0x30, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1c, 0x8, 0x0},
{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x38, 0x3c, 0x3c, 0x3c, 0x24, 0x24, 0x24, 0x20, 0x0},
{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x38, 0x38, 0x28, 0x28, 0x28, 0x28, 0x2c, 0x0, 0x0},
{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x18, 0x2c, 0x24, 0x24, 0x24, 0x2c, 0x18, 0x10, 0x0},
{0x0, 0x0, 0x0, 0x0, 0x0, 0x10, 0x38, 0x2c, 0x24, 0x24, 0x24, 0x2c, 0x38, 0x38, 0x20, 0x20},
{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x18, 0x38, 0x28, 0x28, 0x28, 0x28, 0x18, 0x18, 0x8, 0x8},
{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1c, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x0, 0x0},
{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8, 0x18, 0x30, 0x30, 0x18, 0x8, 0x8, 0x38, 0x18, 0x0},
{0x0, 0x0, 0x0, 0x0, 0x0, 0x10, 0x10, 0x3c, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1c, 0x8, 0x0},
{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x28, 0x28, 0x28, 0x28, 0x28, 0x38, 0x18, 0x18, 0x0},
{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x24, 0x24, 0x28, 0x18, 0x18, 0x18, 0x18, 0x0, 0x0},
{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x24, 0x24, 0x3c, 0x3c, 0x3c, 0x38, 0x38, 0x0, 0x0},
{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x24, 0x18, 0x18, 0x18, 0x18, 0x18, 0x2c, 0x24, 0x0},
{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x24, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x10, 0x30, 0x30},
{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x18, 0x18, 0x8, 0x18, 0x10, 0x10, 0x38, 0x18, 0x0}
};


#endif
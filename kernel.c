#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "util.h"
#include "interrupt/idt.h"
#include "gdt/gdt.h"
#include "screen/framebuffer.h"
#include "stdlib/stdio.h"
#include "multiboot.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif


uint32_t* ba;
void kernel_main(unsigned long magic, unsigned long addr) 
{
	struct multiboot_info* info = (struct multiboot_info*)addr;
	uint32_t* buffer = (uint32_t*)info->framebuffer_addr;
	init_screen(buffer, info->framebuffer_width, info->framebuffer_height);
	printf("hello there\n");
	initGdt();
	initIdt();
	/* Initialize terminal interface */
	// TODO: check for the magic number
	if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
		// printf("Magic number is invalid\n");
		return;
	} else {
		// printf("Magic number is valid: %x\n", magic);
	}
	// obtaining the video information here
	// printf("Framebuffer information : %x\n", info->framebuffer_addr);
	// printf("Flags: %x\n", info->flags);

	for (;;);
	return;
}

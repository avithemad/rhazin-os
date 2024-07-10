#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "util.h"
#include "interrupt/idt.h"
#include "gdt/gdt.h"
#include "vga/vga_text.h"
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

extern void _start();
void kernel_main(unsigned long magic, unsigned long addr) 
{
	struct multiboot_info* info = (struct multiboot_info*)addr;
	uint16_t* buffer = (uint16_t*)info->framebuffer_addr;
	init_screen(buffer);
	printf("Welcome to rhazin OS\n");
	// init_screen(buffer, info->framebuffer_width, info->framebuffer_height);
	initGdt();
	initIdt();
	if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
		printf("Magic number is invalid\n");
		return;
	} 
	// get the memory maps
	uint32_t mmp_len = info->mmap_length;

	for (int i=0; i < mmp_len; i+=sizeof(struct multiboot_mmap_entry)) {
		struct multiboot_mmap_entry* mmap_entry = 
			(struct multiboot_mmap_entry*)(info->mmap_addr + i);

		printf("adr_low: %x, adr_high: %x\n", mmap_entry->addr_low, mmap_entry->addr_high);
		printf(" len_low: %x. len_high: %x\n\n", mmap_entry->len_low, mmap_entry->len_high);
	}
	printf("_start addr: %x", &_start);

	for (;;);
	return;
}

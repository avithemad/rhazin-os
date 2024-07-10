/* Declare constants for the multiboot header. */
.set ALIGN,    1<<0             /* align loaded modules on page boundaries */
.set MEMINFO,  1<<1             /* provide memory map */
.set VIDEOFLAG, 1<<2
.set FLAGS,    ALIGN | MEMINFO | VIDEOFLAG /* this is the Multiboot 'flag' field */
.set MAGIC,    0x1BADB002       /* 'magic number' lets bootloader find the header */
.set CHECKSUM, -(MAGIC + FLAGS) /* checksum of above, to prove we are multiboot */

.section .multiboot, "aw"
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM
.long 0
.long 0
.long 0
.long 0
.long 0
// set width, height and depth for video mode
.long 1
.long 640
.long 400
.long 32

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .boot, "a"
.global _start
.type _start, @function

_start:
	// the start location is now at higher half 
	// on the cr3 register we need to load the physical a.longress of 
	// the initial_page_dir, therefore we subtract the higher half
	// to obtain the physical a.longress
	MOV $initial_page_dir, %ecx
	subl $0xC0000000, %ecx
	mov %ecx, %cr3

	// now actually enable the paging by setting a few control registers
	mov %cr4, %ecx
	or $0x10, %ecx
	mov %ecx, %cr4

	mov  %cr0, %ecx
	or $0x80000000, %ecx
	mov  %ecx, %cr0

	jmp higher_half


.section .text
higher_half:
	mov $stack_top, %esp
	pushl %ebx // multiboot structure
	pushl %eax //magic value

	call kernel_main
	cli	
1:	hlt
	jmp 1b

.section .data
.align 4096
.global initial_page_dir
initial_page_dir:
	.long 0b10000011
	.rept 767
		.long 0
	.endr

	.long (0 << 22) | 0b10000011
	.long (1 << 22) | 0b10000011
	.long (2 << 22) | 0b10000011
	.long (3 << 22) | 0b10000011
	.rept 252
		.long 0
	.endr


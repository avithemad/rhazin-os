/* Declare constants for the multiboot header. */
.set ALIGN,    1<<0             /* align loaded modules on page boundaries */
.set MEMINFO,  1<<1             /* provide memory map */
.set VIDEOFLAG, 1<<2
.set FLAGS,    ALIGN | MEMINFO | VIDEOFLAG /* this is the Multiboot 'flag' field */
.set MAGIC,    0x1BADB002       /* 'magic number' lets bootloader find the header */
.set CHECKSUM, -(MAGIC + FLAGS) /* checksum of above, to prove we are multiboot */

.section .multiboot
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
.long 0
.long 640
.long 480
.long 32

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text
.global _start
.type _start, @function
_start:
	mov $stack_top, %esp


	pushl %ebx // multiboot structure
	pushl %eax //magic value

	call kernel_main
	cli	
1:	hlt
	jmp 1b

.size _start, . - _start

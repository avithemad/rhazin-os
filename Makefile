CFLAGS?=-std=gnu99 -ffreestanding -O0 -Wall -g
kernel:
	${CROSS_COMPILER_PATH}/i686-elf-gcc -c kernel.c -o kernel.o $(CFLAGS) 
	${CROSS_COMPILER_PATH}/i686-elf-as boot.s -o boot.o 
	${CROSS_COMPILER_PATH}/i686-elf-gcc -c util.c -o util.o $(CFLAGS) 
	${CROSS_COMPILER_PATH}/i686-elf-gcc -c interrupt/idt.c -o idt.o $(CFLAGS) 
	${CROSS_COMPILER_PATH}/i686-elf-gcc -c gdt/gdt.c -o gdt.o $(CFLAGS) 
	nasm -f elf32 interrupt/idt.s -o idts.o
	nasm -f elf32 gdt/gdt.s -o gdts.o
	${CROSS_COMPILER_PATH}/i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib \
		boot.o kernel.o util.o idt.o idts.o gdt.o gdts.o -lgcc
	# mkdir -p build/boot/grub
	# cp myos.bin build/boot/myos.bin
	# cp grub.cfg build/boot/grub/grub.cfg
	# grub-mkrescue -o myos.iso build

clean:
	rm *.o *.bin *.iso
	rm -rf build

run:
	qemu-system-i386 -kernel myos.bin
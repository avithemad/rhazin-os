# Design goals of the OS

Write in the problems faces in current operating systems, and what your operating system
intends to solve. 

Do not try to be generic, instead we can focus on a specific type of computation,
one where hardware is heavily needed like in case of web applications
or one where compute is heavily needed and not much of other hardware 
target one niche for now. 

Do you really require drivers in the new os? can't we give the access to the hardware resource
directly to the user with very thin layer of abstractions? why switch to kernel mode just to do
a print on the console, this comes in specifically in linux since everything is treated as a file.
Is this the right abstraction. It definitely provides ease of programming but really can we not
find a better abstraction to do such things?

## TODO logs

1. Add a good terminal support to print your characters and manage the video buffer.
2. Figure out keycodes for the keyboard and add typing support
    -> add formatted printing of int, hex, char, string and float
    -> add support for backspace and tabs
    -> add support for caps lock and shift key
3. Implement paging in order to manage memory
4. Check what features the multiboot provides.
5. How to do a multithreading
6. figure out a strategy for filesystems and user space.

## Milestones

0. Get the bare bones working : done 
1. Setup Gdt, interrupts and get keyboard working  (at least some sort of response from keyboard) : 
2. Have a decent printing and input mechanism.
2. Implement paging, and get the memory management in order.
3. Figure out how to use other processors for multithreading
4. Decide on features for a filesystem and user space and libc.

Now I have the loaded the kernel in the higher half, in physical address space it looks something like this

0x00000000 | this first 2 MB is for the bootloader, which we are using as GRUB
0x00201000 | the kernel(higher half) starts from here (as you can see from the linker.ld)
0x0020A8E0 | end of the kernel

now, we need to create the page table entry and map the page directory entry to the
page table entry. 


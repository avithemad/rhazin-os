global gdt_flush

gdt_flush:
    mov eax, [esp+4]
    lgdt [eax]

    mov eax, 0x10
    mov ds, ax 
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    JMP 0x08:.flush 
.flush:
    RET 


global tss_flush
tss_flush:
    mov ax, 0x28
    LTR ax 
    RET
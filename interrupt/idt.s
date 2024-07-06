global idt_flush
idt_flush:
    mov eax, [esp+4]
    lidt [eax]
    sti 
    ret

%macro ISR_NOERRCODE 1
    global isr%1
    isr%1:
        CLI 
        PUSH LONG 0
        PUSH LONG %1
        JMP isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
    global isr%1
    isr%1:
        CLI 
        PUSH LONG %1
        JMP isr_common_stub
%endmacro


ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7

ISR_ERRCODE 8
ISR_NOERRCODE 9 
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31
ISR_NOERRCODE 128
ISR_NOERRCODE 177


ISR_NOERRCODE 32 
ISR_NOERRCODE 33 
ISR_NOERRCODE 34 
ISR_NOERRCODE 35 
ISR_NOERRCODE 36 
ISR_NOERRCODE 37 
ISR_NOERRCODE 38 
ISR_NOERRCODE 39 
ISR_NOERRCODE 40 
ISR_NOERRCODE 41 
ISR_NOERRCODE 42 
ISR_NOERRCODE 43 
ISR_NOERRCODE 44 
ISR_NOERRCODE 45 
ISR_NOERRCODE 46 
ISR_NOERRCODE 47 
extern isr_handler
isr_common_stub:
    pusha 
    mov eax, ds
    push  eax
    mov eax, cr2
    push eax 

    mov ax, 0x10
    mov ds, ax
    mov es, ax 
    mov fs, ax 
    mov gs, ax 

    push esp 
    call isr_handler

    add esp, 8
    pop ebx
    mov ds, bx
    mov es, bx 
    mov fs, bx 
    mov gs, bx 

    popa 
    add esp, 8
    sti 
    iret
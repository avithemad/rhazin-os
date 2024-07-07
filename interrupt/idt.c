#include "idt.h"
#include "../vga.h"

#define PIC_MASTER_COM 0x20
#define PIC_MASTER_DATA 0x21
#define PIC_SLAVE_COM 0xA0
#define PIC_SLAVE_DATA 0xA1

struct idt_entry idt_entries[256];
struct idt_ptr idt_ptr;

void initIdt() {
    idt_ptr.limit = sizeof(struct idt_entry)*256 - 1;
    idt_ptr.base = (uint32_t)&idt_entries;
    memset(&idt_entries, 0, sizeof(struct idt_entry) * 256);
    // we need to program the programmable interrupt controller
    // in order to resolve the conflicting exceptions and 
    // interrupt offsets that are in the PIC
    // When any event happens in the PIC, it looks at the offset vector
    // adds the corresponding event number to this offset and sends this
    // number as an interrupt to the processor. 
    // Say, vector offset is 0x20 and an interrupt from port 5 comes in then 
    // PIC sends interrupt 0x25 to the processor (As if we send the instruction 
    // ourself, try this out later.)
    // Basic funda is that. So there are 2 controllers master and slave which 
    // provide a total of 16 interrupts 

    outPortB(PIC_MASTER_COM, 0x11);    
    outPortB(PIC_SLAVE_COM, 0x11);    

    // 4 ICW commands to send the data to the PIC
    // 00 to 1F are reserved for exceptions from intel, therefore start from 20
    outPortB(PIC_MASTER_DATA, 0x20);
    outPortB(PIC_SLAVE_DATA, 0x28);
    outPortB(PIC_MASTER_DATA, 0x04);
    outPortB(PIC_SLAVE_DATA, 0x02);
    outPortB(PIC_MASTER_DATA, 0x01);
    outPortB(PIC_SLAVE_DATA, 0x01);
    outPortB(PIC_MASTER_DATA, 0x00);
    outPortB(PIC_SLAVE_DATA, 0x00);


    // need to setup the valid code setup via GDT
    // 0-31 for the instruction exceptions by intel
    setIdtEntry(0, (uint32_t)isr0, 0x08, 0x8E);
    setIdtEntry(1, (uint32_t)isr1, 0x08, 0x8E);
    setIdtEntry(2, (uint32_t)isr2, 0x08, 0x8E);
    setIdtEntry(3, (uint32_t)isr3, 0x08, 0x8E);
    setIdtEntry(4, (uint32_t)isr4, 0x08, 0x8E);
    setIdtEntry(5, (uint32_t)isr5, 0x08, 0x8E);
    setIdtEntry(6, (uint32_t)isr6, 0x08, 0x8E);
    setIdtEntry(7, (uint32_t)isr7, 0x08, 0x8E);
    setIdtEntry(8, (uint32_t)isr8, 0x08, 0x8E);
    setIdtEntry(9, (uint32_t)isr9, 0x08, 0x8E);
    setIdtEntry(10, (uint32_t)isr10, 0x08, 0x8E);
    setIdtEntry(11, (uint32_t)isr11, 0x08, 0x8E);
    setIdtEntry(12, (uint32_t)isr12, 0x08, 0x8E);
    setIdtEntry(13, (uint32_t)isr13, 0x08, 0x8E);
    setIdtEntry(14, (uint32_t)isr14, 0x08, 0x8E);
    setIdtEntry(15, (uint32_t)isr15, 0x08, 0x8E);
    setIdtEntry(16, (uint32_t)isr16, 0x08, 0x8E);
    setIdtEntry(17, (uint32_t)isr17, 0x08, 0x8E);
    setIdtEntry(18, (uint32_t)isr18, 0x08, 0x8E);
    setIdtEntry(19, (uint32_t)isr19, 0x08, 0x8E);
    setIdtEntry(20, (uint32_t)isr20, 0x08, 0x8E);
    setIdtEntry(21, (uint32_t)isr21, 0x08, 0x8E);
    setIdtEntry(22, (uint32_t)isr22, 0x08, 0x8E);
    setIdtEntry(23, (uint32_t)isr23, 0x08, 0x8E);
    setIdtEntry(24, (uint32_t)isr24, 0x08, 0x8E);
    setIdtEntry(25, (uint32_t)isr25, 0x08, 0x8E);
    setIdtEntry(26, (uint32_t)isr26, 0x08, 0x8E);
    setIdtEntry(27, (uint32_t)isr27, 0x08, 0x8E);
    setIdtEntry(28, (uint32_t)isr28, 0x08, 0x8E);
    setIdtEntry(29, (uint32_t)isr29, 0x08, 0x8E);
    setIdtEntry(30, (uint32_t)isr30, 0x08, 0x8E);
    setIdtEntry(31, (uint32_t)isr31, 0x08, 0x8E);

    setIdtEntry(32, (uint32_t)isr32, 0x08, 0x8E);
    setIdtEntry(33, (uint32_t)isr33, 0x08, 0x8E);
    setIdtEntry(34, (uint32_t)isr34, 0x08, 0x8E);
    setIdtEntry(35, (uint32_t)isr35, 0x08, 0x8E);
    setIdtEntry(36, (uint32_t)isr36, 0x08, 0x8E);
    setIdtEntry(37, (uint32_t)isr37, 0x08, 0x8E);
    setIdtEntry(38, (uint32_t)isr38, 0x08, 0x8E);
    setIdtEntry(39, (uint32_t)isr39, 0x08, 0x8E);
    setIdtEntry(40, (uint32_t)isr40, 0x08, 0x8E);
    setIdtEntry(41, (uint32_t)isr41, 0x08, 0x8E);
    setIdtEntry(42, (uint32_t)isr42, 0x08, 0x8E);
    setIdtEntry(43, (uint32_t)isr43, 0x08, 0x8E);
    setIdtEntry(44, (uint32_t)isr44, 0x08, 0x8E);
    setIdtEntry(45, (uint32_t)isr45, 0x08, 0x8E);
    setIdtEntry(46, (uint32_t)isr46, 0x08, 0x8E);
    setIdtEntry(47, (uint32_t)isr47, 0x08, 0x8E);

    // // 128 to 177 for system calls that will be interrupted later
    setIdtEntry(128, (uint32_t)isr128, 0x08, 0x8E);
    setIdtEntry(177, (uint32_t)isr177, 0x08, 0x8E);
    
    idt_flush((uint32_t)&idt_ptr);
    print("Intrrupt descriptor table setup done\n");
};

void setIdtEntry(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags) {
    idt_entries[num].offset_low = base & 0xFFFF;
    idt_entries[num].offset_high = (base >> 16) & 0xFFFF;

    idt_entries[num].segment_selector = selector;

    idt_entries[num].reserved = 0;

    idt_entries[num].flags = flags | 0x60;
}

char* messages[] = {
    "divide by 0",
    "reserved",
    "nmi interrupt",
    "break point",
    "overflow",
    "bounds range exceeded",
    "invalid opcode",
    "device not available",
    "double fault",
    "coprocessor segment overrun",
    "invalid tss",
    "segment not present",
    "stack segment fault",
    "general protection",
    "page fault",
    "reserved",
    "x87 FPU error",
    "Alignment check",
    "Machine chedk",
    "SIMD check",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved"
};
const uint32_t UNKNOWN = 'U';
const uint32_t ESC = 'U';
const uint32_t LSHFT = 'U';
const uint32_t RSHFT = 'U';
const uint32_t CTRL = 'U';
const uint32_t ALT = 'U';
const uint32_t CAPS = 'U';
const uint32_t F1 = 'U';
const uint32_t F2 = 'U';
const uint32_t F3 = 'U';
const uint32_t F4 = 'U';
const uint32_t F5 = 'U';
const uint32_t F6 = 'U';
const uint32_t F7 = 'U';
const uint32_t F8 = 'U';
const uint32_t F9 = 'U';
const uint32_t F10 = 'U';
const uint32_t F11 = 'U';
const uint32_t F12 = 'U';
const uint32_t NUMLCK = 'U';
const uint32_t SCRLCK = 'U';
const uint32_t HOME = 'U';
const uint32_t UP = 'U';
const uint32_t PGUP = 'U';
const uint32_t LEFT = 'U';
const uint32_t RIGHT = 'U';
const uint32_t END = 'U';
const uint32_t DOWN = 'U';
const uint32_t PGDOWN = 'U';
const uint32_t INS = 'U';
const uint32_t DEL = 'U';

const char scan_code_array[128] = {
UNKNOWN,ESC,'1','2','3','4','5','6','7','8',
'9','0','-','=','\b','\t','q','w','e','r',
't','y','u','i','o','p','[',']','\n',CTRL,
'a','s','d','f','g','h','j','k','l',';',
'\'','`',LSHFT,'\\','z','x','c','v','b','n','m',',',
'.','/',RSHFT,'*',ALT,' ',CAPS,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,NUMLCK,SCRLCK,HOME,UP,PGUP,'-',LEFT,UNKNOWN,RIGHT,
'+',END,DOWN,PGDOWN,INS,DEL,UNKNOWN,UNKNOWN,UNKNOWN,F11,F12,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN
};

void isr_handler(struct interrupt_registers* regs){
    if (regs->int_no < 32) {
        print(messages[regs->int_no]);

    } else if (regs->int_no == 33)  {
        uint16_t key_code = inPortB(0x60) & 0x7F;
        uint8_t released = (inPortB(0x60) & 0x80) >> 7;
        char s[] = {scan_code_array[key_code], '\0'};

        if (!released)
            print(s);
    }
    if (regs->int_no >=32) {
        outPortB(0x20, 0x20);
    }
    if (regs->int_no >= 40) {
        outPortB(0xA0, 0x20);
    }
}
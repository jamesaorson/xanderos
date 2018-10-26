#include "idt.h"
#include "../kernel/util.h"

void set_idt_gate(int n, u32 handler) {
    idt[n].lowOffset = low16(handler);
    idt[n].selector = KERNEL_SEGMENT;
    idt[n].always0 = 0;
    idt[n].flags = 0x8E; 
    idt[n].highOffset = high16(handler);
}

void set_idt() {
    idtRegister.base = (u32) &idt;
    idtRegister.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;

    /* Don't make the mistake of loading &idt -- always load &idtRegister */
    __asm__ __volatile__("lidtl (%0)" : : "r" (&idtRegister));
}
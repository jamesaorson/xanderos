#ifndef IDT_H
#define IDT_H

#include "type.h"

/* Segment selectors */
#define KERNEL_SEGMENT 0x08

/* How every interrupt gate (handler) is defined */
typedef struct {
    /* Lower 16 bits of handler function address */
    u16 lowOffset;
    /* Kernel segment selector */
    u16 selector; 
    u8 always0;
    /* First byte
     * Bit 7: "Interrupt is present"
     * Bits 6-5: Privilege level of caller (0=kernel..3=user)
     * Bit 4: Set to 0 for interrupt gates
     * Bits 3-0: bits 1110 = decimal 14 = "32 bit interrupt gate" */
    u8 flags; 
    /* Higher 16 bits of handler function address */
    u16 highOffset;
} __attribute__((packed)) idt_gate_t ;

/* A pointer to the array of interrupt handlers.
 * Assembly instruction 'lidt' will read it */
typedef struct {
    u16 limit;
    u32 base;
} __attribute__((packed)) idt_register_t;

#define IDT_ENTRIES 256
idt_gate_t idt[IDT_ENTRIES];
idt_register_t idtRegister;

/* Functions implemented in idt.c */
void setIdtGate(int n, u32 handler);
void setIdt();

#endif
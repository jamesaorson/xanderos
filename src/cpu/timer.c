#include "timer.h"

#include "../libc/function.h"
#include "isr.h"
#include "ports.h"
#include "types.h"

u32 tick = 0;

static void timerCallback(registers_t registers) {
    tick++;
    UNUSED(registers);
}

void initTimer(u32 freq) {
    /* Install the function we just wrote */
    registerInterruptHandler(IRQ0, timerCallback);

    /* Get the PIT value: hardware clock at 1193180 Hz */
    u32 divisor = 1193180 / freq;
    u8 low  = (u8)(divisor & 0xFF);
    u8 high = (u8)((divisor >> 8) & 0xFF);
    
    /* Send the command */
    /* Command port */
    setPortByte(0x43, 0x36);
    setPortByte(0x40, low);
    setPortByte(0x40, high);
}

#include "timer.h"

#include "../libc/function.h"
#include "isr.h"
#include "ports.h"
#include "type.h"

uint32_t tick = 0;

static void timerCallback(registers_t registers) {
    tick++;
    UNUSED(registers);
}

void initTimer(uint32_t freq) {
    /* Install the function we just wrote */
    registerInterruptHandler(IRQ0, timerCallback);

    /* Get the PIT value: hardware clock at 1193180 Hz */
    uint32_t divisor = 1193180 / freq;
    uint8_t low  = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)((divisor >> 8) & 0xFF);
    
    /* Send the command */
    /* Command port */
    setPortByte(0x43, 0x36);
    setPortByte(0x40, low);
    setPortByte(0x40, high);
}

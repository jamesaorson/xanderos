#include "../drivers/video.h"
#include "../kernel/util.h"
#include "isr.h"
#include "timer.h"

u32 tick = 0;

static void timerCallback(registers_t registers) {
    tick++;
    kprint("Tick: ");
    
    char tickString[256];
    intToString(tick, tickString);
    kprint(tickString);
    kprint("\n");
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

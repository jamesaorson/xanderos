#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"

void main() {
    isrInstall();

    asm volatile("sti");
    initTimer(50);
    /* Comment out the timer IRQ handler to read
     * the keyboard IRQs easier */
    initKeyboard();
}
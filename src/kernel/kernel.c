#include "kernel.h"

#include "../cpu/isr.h"
#include "../drivers/video.h"
#include "../libc/string.h"

void main() {
    isrInstall();
    irqInstall();
}

void userInput(char* input) {
    if (strcmp(input, "END") == 0) {
        kprint("Stopping the CPU.\n");
        asm volatile("hlt");
    }
    kprint("You said: ");
    kprint(input);
    kprint("\n> ");
}
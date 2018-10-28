#include "kernel.h"

#include "../cpu/isr.h"
#include "../drivers/video.h"
#include "../libc/string.h"

void main() {
    isrInstall();
    irqInstall();

    clearScreen();
    kprint("XanderOS> ");
}

void performUserCommand(char* input) {
    kprint("\r");
    if (strcmp(input, "END") == 0) {
        kprint("\nStopping the CPU");
        asm volatile("hlt");
    } else if (strcmp(input, "CLEAR") == 0) {
        clearScreen();
    } else if (strcmp(input, "HEX") == 0) {
        char str[10];
        hexToAscii(15, str);
        kprint(str);
    } else {
        kprint("You said: ");
        kprint(input);
    }
    kprint("\r\nXanderOS> ");
}
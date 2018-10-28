#include "kernel.h"

#include "../cpu/isr.h"
#include "../drivers/video.h"
#include "../libc/string.h"

void clearCommand(char* prompt) {
    clearScreen();
    kprint(prompt);
}

void endCommand() {
    kprint("\nStopping the CPU");
    asm volatile("hlt");
}

void hexCommand(int hex) {
    char str[10];
    hexToAscii(hex, str);
    kprint(str);
}

void kernelMain() {
    isrInstall();
    irqInstall();

    clearScreen();
    kprint("XanderOS> ");
}

void performUserCommand(char* input) {
    kprint("\r");
    if (strcmp(input, "END") == 0) {
        endCommand();
    } else if (strcmp(input, "CLEAR") == 0) {
        clearCommand("XanderOS> ");    
        return;
    } else if (strcmp(input, "HEX") == 0) {
        hexCommand(15);
    } else {
        kprint("You said: ");
        kprint(input);
    }
    kprint("\r\nXanderOS> ");
}

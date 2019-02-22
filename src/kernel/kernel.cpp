#include "kernel.h"

#include "../cpu/isr.h"
#include "../drivers/video.h"
#include "../libc/string.h"

int hexNum = 0;

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

void threadCommand() {

}

extern "C" void kernelMain() {
    isrInstall();
    irqInstall();

    clearScreen();
    char splashScreen [6][36] = {
        "     ____  ___    _   _______  __ \n",
        "    / __ \\/   |  / | / /  _/ |/ /\n",
        "   / /_/ / /| | /  |/ // / |   /  \n",
        "  / ____/ ___ |/ /|  // / /   |   \n",
        " /_/   /_/  |_/_/ |_/___//_/|_|   \n",
        "\nWelcome to the PANIX kernel!\n"
    };
    for (int i = 0; i < 6; i++) {
        kprint(splashScreen[i]);
    }
}

void performUserCommand(char* input) {
    kprint("\r");
    if (strcmp(input, "END") == 0) {
        endCommand();
    } else if (strcmp(input, "CLEAR") == 0) {
        clearCommand("XanderOS> ");    
        return;
    } else if (strcmp(input, "HEX") == 0) {
        if (hexNum == 15) {
            hexNum = 0;
        }
        hexCommand(hexNum++);
    } else {
        kprint("You said: ");
        kprint(input);
    }
    kprint("\r\nXanderOS> ");
}

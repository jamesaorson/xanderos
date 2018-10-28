#include "keyboard.h"

#include "../cpu/isr.h"
#include "../kernel/kernel.h"
#include "../libc/function.h"
#include "../libc/string.h"
#include "../cpu/ports.h"
#include "video.h"

#define BACKSPACE 0x0E
#define ENTER 0x1C

static char keyBuffer[256];

#define SC_MAX 57
const char* scancodeNames[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
                                "7", "8", "9", "0", "-", "=", "Backspace", "Tab", 
                                "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", 
                                "[", "]", "Enter", "Lctrl", "A", "S", "D", "F", 
                                "G", "H", "J", "K", "L", ";", "'", "`", "LShift", 
                                "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
                                "/", "RShift", "Keypad *", "LAlt", "Spacebar"
                              };
const char scancodeAscii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
                          '7', '8', '9', '0', '-', '=', '?', '?', 
                          'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 
                          'O', 'P', '[', ']', '?', '?', 'A', 'S', 
                          'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', 
                          '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
                          'B', 'N', 'M', ',', '.', '/', '?', '?', 
                          '?', ' '
                        };

static void keyboardCallback(registers_t regs) {
    /* The PIC leaves us the scancode in port 0x60 */
    u8 scancode = getPortByte(0x60);
    
    if (scancode > SC_MAX) {
        return;
    }
    if (scancode == BACKSPACE) {
        backspace(keyBuffer);
        kprintBackspace();
    } else if (scancode == ENTER) {
        kprint("\n");
        performUserCommand(keyBuffer); /* kernel-controlled function */
        keyBuffer[0] = '\0';
    } else {
        char letter = scancodeAscii[(int)scancode];
        /* Remember that kprint only accepts char[] */
        char str[2] = {letter, '\0'};
        strappend(keyBuffer, letter);
        kprint(str);
    }
    UNUSED(regs);
}

void initKeyboard() {
   registerInterruptHandler(IRQ1, keyboardCallback); 
}
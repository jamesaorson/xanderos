#include "../drivers/video.h"
#include "util.h"

void main() {
    clearScreen();

    /* Fill up the screen */
    int i = 0;
    for (i = 0; i < 24; i++) {
        char str[255];
        intToString(i, str);
        printkAtPosition(str, i, 0);
    }

    printkAtPosition("This text forces the kernel to scroll. Row 0 will disappear. ", 24, 60);
    printkAtPosition("This text forces the kernel to scroll. Row 1 will disappear. ", 24, 60);
    printkAtPosition("This text forces the kernel to scroll. Row 2 will disappear. ", 24, 60);
    printkAtPosition("This text forces the kernel to scroll. Row 3 will disappear. ", 24, 60);
    printk("This text forces the kernel to scroll. Row 4 will disappear. ");
}
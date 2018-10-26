#include "../drivers/video.h"

void main() {
    clearScreen();
    printkAtPosition("X", 6, 1);
    printkAtPosition("This text spans multiple lines", 10, 0);
    printkAtPosition("There is a line\nbreak", 20, 0);
    printk("There is a line\nbreak");
    printkAtPosition("What happens when we run out of space?", 24, 45);
}
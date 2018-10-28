#include "memory.h"

void memoryCopy(char *source, char *dest, int numberOfBytes) {
    int i;
    for (i = 0; i < numberOfBytes; i++) {
        *(dest + i) = *(source + i);
    }
}

void memorySet(u8* destination, u8 value, u32 length) {
    u8* temp = (u8*) destination;
    for ( ; length != 0; length--) {
        *temp++ = value;
    }
}
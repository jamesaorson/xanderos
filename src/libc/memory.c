#include "memory.h"

#include "../cpu/type.h"

/* This should be computed at link time, but a hardcoded
 * value is fine for now. Remember that our kernel starts
 * at 0x1000 as defined on the Makefile */
u32 freeMemoryAddress = 0x10000;

/* Implementation is just a pointer to some free memory which
 * keeps growing */
u32 kmalloc(u32 size, int align, u32* physicalAddress) {
    /* Pages are aligned to 4K, or 0x1000 */
    if (align == 1 && (freeMemoryAddress & 0xFFFFF000)) {
        freeMemoryAddress &= 0xFFFFF000;
        freeMemoryAddress += 0x1000;
    }
    /* Save also the physical address */
    if (physicalAddress) {
        *physicalAddress = freeMemoryAddress;
    }

    u32 result = freeMemoryAddress;
    freeMemoryAddress += size;
    return result;
}

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
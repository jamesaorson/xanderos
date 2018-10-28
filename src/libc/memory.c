#include "memory.h"

#include "../cpu/type.h"

/* This should be computed at link time, but a hardcoded
 * value is fine for now. Remember that our kernel starts
 * at 0x1000 as defined on the Makefile */
uint32_t freeMemoryAddress = 0x10000;

/* Implementation is just a pointer to some free memory which
 * keeps growing */
uint32_t kmalloc(uint32_t size, int align, uint32_t* physicalAddress) {
    /* Pages are aligned to 4K, or 0x1000 */
    if (align == 1 && (freeMemoryAddress & 0xFFFFF000)) {
        freeMemoryAddress &= 0xFFFFF000;
        freeMemoryAddress += 0x1000;
    }
    /* Save also the physical address */
    if (physicalAddress) {
        *physicalAddress = freeMemoryAddress;
    }

    uint32_t result = freeMemoryAddress;
    freeMemoryAddress += size;
    return result;
}

void memoryCopy(char *source, char *dest, int numberOfBytes) {
    int i;
    for (i = 0; i < numberOfBytes; i++) {
        *(dest + i) = *(source + i);
    }
}

void memorySet(uint8_t* destination, uint8_t value, uint32_t length) {
    uint8_t* temp = (uint8_t*) destination;
    for ( ; length != 0; length--) {
        *temp++ = value;
    }
}
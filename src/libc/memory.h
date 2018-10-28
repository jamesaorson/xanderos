#ifndef MEMORY_H
#define MEMORY_H

#include "../cpu/type.h"

u32 kmalloc(u32 size, int align, u32* physicalAddress);

void memoryCopy(char* source, char* dest, int numberOfBytes);
void memorySet(u8* destination, u8 value, u32 length);

#endif
#ifndef MEMORY_H
#define MEMORY_H

#include "../cpu/types.h"

void memoryCopy(char* source, char* dest, int numberOfBytes);
void memorySet(u8* destination, u8 value, u32 length);

#endif
#ifndef MEMORY_H
#define MEMORY_H

#include "../cpu/type.h"
#include <stddef.h>

uint32_t kmalloc(size_t size, int align, uint32_t* physicalAddress);

void memoryCopy(char* source, char* dest, int numberOfBytes);
void memorySet(uint8_t* destination, uint8_t value, uint32_t length);

#endif
#ifndef UTIL_H
#define UTIL_H

#include "../cpu/types.h"

void memoryCopy(char* source, char* dest, int numberOfBytes);
void memorySet(u8* destination, u8 value, u32 length);
void intToString(int number, char outputString[]);
void reverseString(char stringToReverse[]);
int strlen(char str[]);

#endif
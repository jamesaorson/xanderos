#ifndef STRING_H
#define STRING_H

#include "../cpu/types.h"

int strlen(char str[]);

void intToString(int number, char outputString[]);
void reverseString(char stringToReverse[]);

#endif
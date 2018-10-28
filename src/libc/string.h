#ifndef STRING_H
#define STRING_H

#include "../cpu/type.h"

int strcmp(char s1[], char s2[]);
int strlen(char str[]);

void backspace(char s[]);
void hexToAscii(int hex, char str[]);
void intToString(int number, char outputString[]);
void reverseString(char stringToReverse[]);
void strappend(char str[], char characterToAppend);

#endif
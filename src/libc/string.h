#ifndef STRING_H
#define STRING_H

#include "../cpu/type.h"

int strcmp(char s1[], char s2[]);
int strlen(char str[]);

void append(char s[], char n);
void backspace(char s[]);
void intToString(int number, char outputString[]);
void reverseString(char stringToReverse[]);

#endif
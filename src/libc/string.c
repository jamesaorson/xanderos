#include "string.h"

/* K&R 
 * Returns <0 if str1<str2, 0 if str1==str2, >0 if str1>str2 */
int strcmp(char str1[], char str2[]) {
    int i;
    for (i = 0; str1[i] == str2[i]; i++) {
        if (str1[i] == '\0') {
            return 0;
        }
    }
    return str1[i] - str2[i];
}

int strlen(char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }

    return i;
}

void append(char str[], char characterToAppend) {
    int len = strlen(str);
    str[len] = characterToAppend;
    str[len + 1] = '\0';
}

void backspace(char str[]) {
    int length = strlen(str);
    str[length - 1] = '\0';
}

/**
 * K&R implementation
 */
void intToString(int number, char outputString[]) {
    int i = 0;
    int sign = number;
    if (sign < 0) {
        number = -number;
    }
    do {
        outputString[i++] = number % 10 + '0';
    } while ((number /= 10) > 0);
    
    if (sign < 0) {
        outputString[i++] = '-';
    }
    reverseString(outputString);

    outputString[i] = '\0';
}

void reverseString(char stringToReverse[]) {
    int temp, i, j;
    for (i = 0, j = strlen(stringToReverse)-1; i < j; i++, j--) {
        temp = stringToReverse[i];
        stringToReverse[i] = stringToReverse[j];
        stringToReverse[j] = temp;
    }
}
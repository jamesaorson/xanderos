#include "util.h"

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

int strlen(char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }

    return i;
}
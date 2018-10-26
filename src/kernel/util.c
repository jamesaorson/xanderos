void memoryCopy(char *source, char *dest, int numberOfBytes) {
    int i;
    for (i = 0; i < numberOfBytes; i++) {
        *(dest + i) = *(source + i);
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
    reverseString(outputString, i);

    outputString[i] = '\0';
}

void reverseString(char stringToReverse[], int length) {
    int i;
    for (i = 0; i < length / 2; ++i) {
        char temp = stringToReverse[i];
        int swapPosition = length - i - 1;
        stringToReverse[i] = stringToReverse[swapPosition];
        stringToReverse[swapPosition] = temp;
    }
}
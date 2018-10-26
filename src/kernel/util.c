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
    outputString[i] = '\0';
}
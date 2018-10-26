#include "video.h"
#include "ports.h"
#include "../cpu/types.h"
#include "../kernel/util.h"

/* Declaration of private functions */
int getCursorOffset();
int getOffset(int row, int column);
int getOffsetColumn(int offset);
int getOffsetRow(int offset);
int printChar(char character, int row, int column, char color);
void clearScreen();
void setCursorOffset(int offset);

/**********************************************************
 * Public Kernel API functions                            *
 **********************************************************/

/**
 * Print a message on the specified location
 * If column, row, are negative, we will use the current offset
 */
void printkAtPosition(char *message, int row, int column) {
    /* Set cursor if column/row are negative */
    int offset;
    if (column >= 0 && row >= 0)
        offset = getOffset(row, column);
    else {
        offset = getCursorOffset();
        row = getOffsetRow(offset);
        column = getOffsetColumn(offset);
    }

    /* Loop through message and print it */
    int i = 0;
    while (message[i] != 0) {
        offset = printChar(message[i++], row, column, WHITE_ON_BLACK);
        /* Compute row/column for next iteration */
        row = getOffsetRow(offset);
        column = getOffsetColumn(offset);
    }
}

void printk(char *message) {
    printkAtPosition(message, -1, -1);
}

/**********************************************************
 * Private kernel functions                               *
 **********************************************************/


/**
 * Innermost print function for our kernel, directly accesses the video memory 
 *
 * If 'column' and 'row' are negative, we will print at current cursor location
 * If 'color' is zero it will use 'white on black' as default
 * Returns the offset of the next character
 * Sets the video cursor to the returned offset
 */

void clearScreen() {
    int screenSize = MAX_COLUMNS * MAX_ROWS;
    char* screen = (char*) VIDEO_ADDRESS;

    int i;
    for (i = 0; i < screenSize; i++) {
        screen[i * 2] = ' ';
        screen[i * 2 + 1] = WHITE_ON_BLACK;
    }
    setCursorOffset(getOffset(0, 0));
}

int getCursorOffset() {
    /* Use the VGA ports to get the current cursor position
     * 1. Ask for high byte of the cursor offset (data 14)
     * 2. Ask for low byte (data 15)
     */
    setPortByte(SCREEN_CONTROL_PORT, 14);
    /* High byte: << 8 */
    int offset = getPortByte(SCREEN_DATA_PORT) << 8;
    setPortByte(SCREEN_CONTROL_PORT, 15);
    offset += getPortByte(SCREEN_DATA_PORT);
    
    /* Position * size of character cell */
    return offset * 2;
}

int getOffset(int row, int column) {
    return 2 * (row * MAX_COLUMNS + column); 
}

int getOffsetColumn(int offset) {
    return (offset - (getOffsetRow(offset) * 2 * MAX_COLUMNS)) / 2;
}

int getOffsetRow(int offset) {
    return offset / (2 * MAX_COLUMNS);
}

int printChar(char character, int row, int column, char color) {
    u8 *videoAddress = (u8*) VIDEO_ADDRESS;
    if (!color) {
        color = WHITE_ON_BLACK;
    }

    /* Error control: print a red 'E' if the coords aren't right */
    if (column >= MAX_COLUMNS || row >= MAX_ROWS) {
        videoAddress[2 * (MAX_COLUMNS) * (MAX_ROWS) - 2] = 'E';
        videoAddress[2 * (MAX_COLUMNS) * (MAX_ROWS) - 1] = RED_ON_WHITE;
        return getOffset(row, column);
    }

    int offset;
    if (column >= 0 && row >= 0) {
        offset = getOffset(row, column);
    }
    else {
        offset = getCursorOffset();
    }

    if (character == '\n') {
        row = getOffsetRow(offset);
        offset = getOffset(row + 1, column);
    } else {
        videoAddress[offset] = character;
        videoAddress[offset + 1] = color;
        offset += 2;
    }

    /* Check if the offset is over screen size and scroll */
    if (offset >= MAX_ROWS * MAX_COLUMNS * 2) {
        int i;
        for (i = 1; i < MAX_ROWS; i++) 
            memoryCopy((char*) getOffset(i, 0) + VIDEO_ADDRESS,
                       (char*) getOffset(i - 1, 0) + VIDEO_ADDRESS,
                       MAX_COLUMNS * 2);

        /* Blank last line */
        char* lastLine = (char*) getOffset(MAX_ROWS - 1, 0) + VIDEO_ADDRESS;
        for (i = 0; i < MAX_COLUMNS * 2; i++) {
            lastLine[i] = 0;
        }

        offset -= 2 * MAX_COLUMNS;
    }


    setCursorOffset(offset);
    return offset;
}

void setCursorOffset(int offset) {
    /* Similar to getCursorOffset, but instead of reading we write data */
    offset /= 2;
    setPortByte(SCREEN_CONTROL_PORT, 14);
    setPortByte(SCREEN_DATA_PORT, (u8)(offset >> 8));
    setPortByte(SCREEN_CONTROL_PORT, 15);
    setPortByte(SCREEN_DATA_PORT, (u8)(offset & 0xff));
}
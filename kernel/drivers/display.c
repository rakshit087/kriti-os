#include "display.h"
#include "ports.h"

//Declaring Private Helper Functions
int cal_offset(int col, int row);
int cal_offset_row(int offset);
int cal_offset_col(int offset);
int get_cursor();
void set_cursor(int offset);
int print_char(char c, int col, int row, char attr);

/***************************/
/* PUBLIC KERNEL FUNCTIONS */
/***************************/

void cls()
{
    char *screen = (char *)VIDEO_ADDRESS;
    int screen_size = MAX_COLS * MAX_ROWS;
    int i;
    for (i = 0; i < screen_size; i++)
    {
        screen[i * 2] = ' ';
        screen[i * 2 + 1] = WHITE;
    }
    set_cursor(cal_offset(0, 0));
}

void display_at(char *message, int col, int row, char attribute)
{
    int offset;
    if (col >= 0 && row >= 0)
        offset = cal_offset(col, row);
    else
    {
        offset = get_cursor();
        row = cal_offset_row(offset);
        col = cal_offset_col(offset);
    }
    int i = 0;
    while (message[i] != 0)
    {
        offset = print_char(message[i++], col, row, attribute);
        row = cal_offset_row(offset);
        col = cal_offset_col(offset);
    }
}

void display(char *message, char attribute)
{
    display_at(message, -1, -1, attribute);
}

/****************************/
/* PRIVATE HELPER FUNCTIONS */
/****************************/

/**
The framebuffer is available at the address 0xB8000
The offset from the start of the framebuffer of the word that specifies a character at position x, y is:
(y * 80 + x) * 2 (because 80 is max no of rows)
**/
int cal_offset(int col, int row)
{
    return 2 * (row * MAX_COLS + col);
}
int cal_offset_row(int offset) { return offset / (2 * MAX_COLS); }
int cal_offset_col(int offset) { return (offset - (cal_offset_row(offset) * 2 * MAX_COLS)) / 2; }

int get_cursor()
{
    outb(SCREEN_CNTRL, 14);             //Switching control to 14 Reg
    int offset = inb(SCREEN_DATA) << 8; //Reading 14th register, since it is upper byte we shift it
    outb(SCREEN_CNTRL, 15);             //Switching control to 15 reg
    offset += inb(SCREEN_DATA);         //calculating total offset as 14th byte + 15th byte
    return offset * 2;                  //multipying by 2 because each display takes 16 bytes (8 for properties and 8 for character)
}

void set_cursor(int offset)
{
    offset /= 2;
    outb(SCREEN_CNTRL, 14);
    outb(SCREEN_DATA, (unsigned char)(offset >> 8)); //writing on 14th reg
    outb(SCREEN_CNTRL, 15);
    outb(SCREEN_DATA, (unsigned char)(offset & 0xff)); //writing on 15th reg
}

int print_char(char c, int col, int row, char attr)
{
    unsigned char *vidmem = (unsigned char *)VIDEO_ADDRESS;
    //In case of no attribute, set the default attribute to White
    if (!attr)
        attr = WHITE;

    //If the position is greator then the possible we print an E.
    if (col >= MAX_COLS || row >= MAX_ROWS)
    {
        vidmem[2 * (MAX_COLS) * (MAX_ROWS)-2] = 'E';
        vidmem[2 * (MAX_COLS) * (MAX_ROWS)-1] = RED;
        return cal_offset(col, row);
    }

    int offset;
    //If offset is not given, we use the cursor offset
    if (col >= 0 && row >= 0)
        offset = cal_offset(col, row);
    else
        offset = get_cursor();

    //Handeling new lines
    if (c == '\n')
    {
        row = cal_offset_row(offset);
        offset = cal_offset(0, row + 1);
    }
    else
    {
        vidmem[offset] = c;
        vidmem[offset + 1] = attr;
        offset += 2;
    }
    set_cursor(offset);
    return offset;
}
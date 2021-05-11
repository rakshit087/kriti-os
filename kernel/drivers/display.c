#include "display.h"
#include "ports.h"
unsigned short *vidmem = (unsigned short *)0xB8000;
unsigned short cursor_x = 0;
unsigned short cursor_y = 2;

//Defining Some Private Helper Functions

static void set_cursor()
{
    
    //The framebuffer is available at the address 0xB8000
    //The offset from the start of the framebuffer of the word that specifies a character at position x, y is:
    //(y * 80 + x) * 2 (because 80 is max no of rows)
    unsigned short cursorLocation = cursor_y * 80 + cursor_x;
    outb(SCREEN_CNTRL, 14);                  // Tell the VGA board we are setting the high cursor byte.
    outb(SCREEN_DATA, cursorLocation >> 8); // Send the high cursor byte.
    outb(SCREEN_CNTRL, 15);                  // Tell the VGA board we are setting the low cursor byte.
    outb(SCREEN_DATA, cursorLocation);      // Send the low cursor byte.
}

// Scrolls the text on the screen up by one line.
static void scroll()
{

    // Get a space character with the default colour attributes.
    unsigned char attributeByte = WHITE;
    unsigned short blank = 0x20 | (attributeByte << 8);

    // Row 25 is the end, this means we need to scroll up
    if(cursor_y >= 25)
    {
        // Move the current text chunk that makes up the screen
        // back in the buffer by a line
        int i;
        for (i = 0; i < 24*80; i++)
        {
            vidmem[i] = vidmem[i+80];
        }

        // The last line should now be blank. Do this by writing
        // 80 spaces to it.
        for (i = 24*80; i < 25*80; i++)
        {
            vidmem[i] = blank;
        }
        // The cursor should now be on the last line.
        cursor_y = 24;
    }
}


//Public Functions for Kernel

//Printing a single character
// Writes a single character out to the screen.
void display_char(char c, unsigned char attributeByte)
{
    // The attribute byte is made up of two nibbles - the lower being the 
    // foreground colour, and the upper the background colour.
    // The attribute byte is the top 8 bits of the word we have to send to the
    // VGA board.
    unsigned short attribute = attributeByte << 8;
    unsigned short *location;

    // Handle a backspace, by moving the cursor back one space
    if (c == 0x08 && cursor_x)
    {
        cursor_x--;
    }

    // Handle a tab by increasing the cursor's X, but only to a point
    // where it is divisible by 8.
    else if (c == 0x09)
    {
        cursor_x = (cursor_x+8) & ~(8-1);
    }

    // Handle carriage return
    else if (c == '\r')
    {
        cursor_x = 0;
    }

    // Handle newline by moving cursor back to left and increasing the row
    else if (c == '\n')
    {
        cursor_x = 0;
        cursor_y++;
    }
    // Handle any other printable character.
    else if(c >= ' ')
    {
        location = vidmem + (cursor_y*80 + cursor_x);
        *location = c | attribute;
        cursor_x++;
    }
    // Check if we need to insert a new line because we have reached the end
    // of the screen.
    if (cursor_x >= 80)
    {
        cursor_x = 0;
        cursor_y ++;
    }
    // Scroll the screen if needed.
    scroll();
    // Move the hardware cursor.
    set_cursor();

}

void display(char *c, unsigned char attribute)
{
    int i = 0;
    while (c[i])
    {
        display_char(c[i++],attribute);
    }
}

void cls() {
    // Make an attribute byte for the default colours
    unsigned char attributeByte = WHITE;
    unsigned short blank = ' ' /* space */ | (attributeByte << 8);

    int i;
    for (i = 0; i < 80*25; i++)
    {
        vidmem[i] = blank;
    }

    // Move the hardware cursor back to the start.
    cursor_x = 0;
    cursor_y = 0;
    set_cursor();
}

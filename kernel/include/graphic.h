#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "isr.h"

#define VGA_GRAPHIC_ADDRESS 0xA0000

typedef struct window
{
  uint32 x, y;
  uint32 height, width;
  uint32 color;
} window_t;

// tell compiler our int32 function is external
extern void rint32(uint8 intnum, registers16_t *regs);

/*
  The function puts a pixel on the screen.

  Input:
    The coordinates of the pixel and it's color.
  Output:
    None.
*/
void put_pixel(int pos_x, int pos_y, int color);

/*
  The function clears the screen.

  Input:
    None.
  Output:
    None.
*/
void clear_graphic();

/*
  The function puts a mouse cursor on the screen.

  Input:
    The coordinates of the mouse and it's color.
  Output:
    None.
*/
void draw_mouse(int pos_x, int pos_y, int color);

/*
  The function puts a rectangle on the screen.

  Input:
    The coordinates of the rectangle, the size of it and it's color.
  Output:
    None.
*/
void draw_rect(int pos_x, int pos_y, int width, int height, int color);

/*
  The function puts an X on the screen.

  Input:
    The coordinates of the X.
  Output:
    None.
*/
void draw_x(int pos_x, int pos_y);

/*
  The function puts a window on the screen.

  Input:
    The window object.
  Output:
    None.
*/
void draw_window(window_t window);

#endif

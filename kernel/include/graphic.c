#include "graphic.h"

/*
  The function puts a pixel on the screen.

  Input:
    The coordinates of the pixel and it's color.
  Output:
    None.
*/
void put_pixel(int pos_x, int pos_y, int color)
{
    uint8* location = (uint8*)VGA_GRAPHIC_ADDRESS + 320 * pos_y + pos_x;
    *location = color;
}

/*
  The function clears the screen.

  Input:
    None.
  Output:
    None.
*/
void clear_graphic()
{
  int i;
  int8* p;

  for(i = 0xa0000; i < 0xaffff; i++)
  {
      p = (int8*)i;
      *p = 15;   //white color
  }
}

/*
  The function puts a mouse cursor on the screen.

  Input:
    The coordinates of the mouse and it's color.
  Output:
    None.
*/
void draw_mouse(int pos_x, int pos_y, int color)
{
  draw_rect(pos_x - 4, pos_y, 10, 2, color);

  draw_rect(pos_x, pos_y - 4, 2, 10, color);
}

/*
  The function puts a rectangle on the screen.

  Input:
    The coordinates of the rectangle, the size of it and it's color.
  Output:
    None.
*/
void draw_rect(int pos_x, int pos_y, int width, int height, int color)
{
    int i = 0, j = 0;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            put_pixel(pos_x + j, pos_y + i, color);
        }
    }
}

/*
  The function puts an X on the screen.

  Input:
    The coordinates of the X.
  Output:
    None.
*/
void draw_x(int pos_x, int pos_y)
{
  for(int i = pos_x, j = pos_y; i < pos_x + 7; i++, j++)
  {
    put_pixel(i, j, 4);
  }
  for(int i = pos_x, j = pos_y + 1; i < pos_x + 7; i++, j++)
  {
    put_pixel(i, j, 4);
  }
  for(int i = pos_x + 6, j = pos_y; i > pos_x - 1; i--, j++)
  {
    put_pixel(i, j, 4);
  }
  for(int i = pos_x + 6, j = pos_y + 1; i > pos_x - 1; i--, j++)
  {
    put_pixel(i, j, 4);
  }
}

/*
  The function puts a window on the screen.

  Input:
    The window object.
  Output:
    None.
*/
void draw_window(window_t window)
{
  draw_rect(window.x, window.y, window.width, 15, 9);
  draw_x(window.x + window.width - 10, window.y + 2);
  draw_rect(window.x, window.y + 15, window.width, window.height, window.color);
  draw_rect(window.x + (window.width / 4), window.y + (window.height / 3), window.width / 2, window.height / 2, 14);
}

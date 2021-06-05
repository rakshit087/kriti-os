#include "mouse.h"

static int8 mouse_byte[3];
static int8 offset = 0;

static int32 mouse_x = 160;
static int32 mouse_y = 100;
static int32 mcolor = 1;

static window_t win;

/*
  The handler of any mouse input.

  Input:
    None.
  Output:
    None.
*/
void mouse_handler()
{
  char printMe[10] = { 0 };
  int8 x_diff = 0, y_diff = 0, test = 0;
  int8 status = inb(0x64);

  int8 input = inb(0x60);

  if (status & 0x20)
  {
    switch(offset)
    {
      case 0:
        mouse_byte[0] = input;
        if (!(input & 0x08)) return;
        offset++;
        break;
      case 1:
        mouse_byte[1] = input;
        offset++;
        break;
      case 2:
        mouse_byte[2] = input;

        if (mouse_byte[0] & 0x80 || mouse_byte[0] & 0x40)
        {
						/* x/y overflow? bad packet! */
            offset = 0;
						break;
				}

        if (mouse_byte[0] & 0x01) // Left Click
        {
            mcolor = 4;
            offset = 0;
            break;
				}
				if (mouse_byte[0] & 0x02) // Right Click
        {
            mcolor = 5;
            offset = 0;
            break;
				}
				if (mouse_byte[0] & 0x04) // Middle Click
        {
            mcolor = 6;
            offset = 0;
            break;
        }


        x_diff = mouse_byte[1] - ((mouse_byte[0] << 4) & 0x100);
        y_diff = mouse_byte[2] - ((mouse_byte[0] << 3) & 0x100);

        mouse_x += mouse_byte[1];
        mouse_y -= mouse_byte[2];

        if(mcolor == 4 && mouse_x >= win.x && mouse_x <= (win.x + win.width)
          && mouse_y >= win.y && mouse_y <= (win.y + win.height + 10) && mouse_x < 320 && mouse_x > 0
          && mouse_y >= 0 && mouse_y <= 200)
        {
          win.x += mouse_byte[1];
          win.y -= mouse_byte[2];
        }

        if(mcolor == 4 && mouse_x >= win.x + win.width - 10
          && mouse_y >= win.y + 2 && mouse_x <= win.x + win.width + 3
          && mouse_y <= win.y + 9)
        { // Remove Window
          win.y = 1000;
          win.x = 1000;
        }

        if(mouse_x < 0)
        {
          mouse_x = 0;
        }
        if(mouse_y < 0)
        {
          mouse_y = 0;
        }
        if(mouse_x > 320)
        {
          mouse_x = 320;
        }
        if(mouse_y > 200)
        {
          mouse_y = 200;
        }


        clear_graphic();

        draw_window(win);
        draw_mouse((uint32)(mouse_x), (uint32)(mouse_y), mcolor);

        offset = 0;
        break;
      }
  }
}

/*
  The function makes the mouse wait.

  Input:
    The type of the wait (data/signal).
  Output:
    None.
*/
void mouse_wait(uint8 a_type)
{
  uint32 time_out = 100000;
  if(a_type == 0)
  {
    while(time_out--) //Data
    {
      if((inb(MOUSE_STATUS) & 0x01)==1)
      {
        return;
      }
    }
    return;
  }
  else
  {
    while(time_out--) //Signal
    {
      if((inb(MOUSE_STATUS) & 0x02) == 0)
      {
        return;
      }
    }
    return;
  }
}

/*
  The function writes a byte to the mouse.

  Input:
    The byte to write.
  Output:
    None.
*/
void mouse_write(uint8 a_write)
{
  //Wait to be able to send a command
  mouse_wait(1);
  //Tell the mouse we are sending a command
  outb(0x64, 0xD4);
  //Wait for the final part
  mouse_wait(1);
  //Finally write
  outb(0x60, a_write);
}

/*
  The function reads a byte from the mouse.

  Input:
    None.
  Output:
    The read byte.
*/
uint8 mouse_read()
{
  //Get a response from mouse
  mouse_wait(0);
  return inb(0x60);
}

/*
  The function initializes the mouse.

  Input:
    None.
  Output:
    None.
*/
void init_mouse()
{
    win.x = 50;
    win.y = 50;
    win.width = 120;
    win.height = 70;
    win.color = 3;

    uint8 status;

    //Enable the auxiliary mouse device
    mouse_wait(1);
    outb(0x64, 0xA8);

    //Enable the interrupts
    mouse_wait(1);
    outb(0x64, 0x20);
    mouse_wait(0);
    status = (inb(0x60) | 2);
    mouse_wait(1);
    outb(0x64, 0x60);
    mouse_wait(1);
    outb(0x60, status);

    //Tell the mouse to use default settings
    mouse_write(0xF6);
    mouse_read();  //Acknowledge

    //Enable the mouse
    mouse_write(0xF4);
    mouse_read();  //Acknowledge

    register_interrupt_handler(44, &mouse_handler);
}

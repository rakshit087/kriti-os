#ifndef MOUSE_H
#define MOUSE_H

#include "isr.h"
#include "graphic.h"
#include "ports.h"

#define MOUSE_IRQ 44

#define MOUSE_PORT   0x60
#define MOUSE_STATUS 0x64

/*
  The handler of any mouse input.

  Input:
    None.
  Output:
    None.
*/
void mouse_handler();

/*
  The function makes the mouse wait.

  Input:
    The type of the wait (data/signal).
  Output:
    None.
*/
void mouse_wait(uint8 a_type);

/*
  The function writes a byte to the mouse.

  Input:
    The byte to write.
  Output:
    None.
*/
void mouse_write(uint8 a_write);

/*
  The function reads a byte from the mouse.

  Input:
    None.
  Output:
    The read byte.
*/
uint8 mouse_read();

/*
  The function initializes the mouse.

  Input:
    None.
  Output:
    None.
*/
void init_mouse();

#endif

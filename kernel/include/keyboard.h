#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "display.h"
#include "types.h"
#include "ports.h"
#include "isr.h"

/*
  The function reads a character from the keyboard.

  Input:
    None.
  Output:
    The read character.
*/
char readChar();

/*
  The function reads a character from the keyboard.

  Input:
    None.
  Output:
    The read character.
*/
void readStr(char* buffstr);

#endif

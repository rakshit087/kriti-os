#ifndef PORTS_H
#define PORTS_H
#include "types.h"
// DECLARING SOME LOW LEVEL FUNCTIONS
void outb(unsigned short port,unsigned char value);
unsigned char inb(unsigned short port);
unsigned short inw(unsigned short port);
uint8 read_register(uint8 reg);
void write_register(uint8 reg, uint8 value);
#endif

#ifndef PORTS_H
#define PORTS_H

// DECLARING SOME LOW LEVEL FUNCTIONS
void outb(unsigned short port,unsigned char value);
unsigned char inb(unsigned short port);
unsigned short inw(unsigned short port);

#endif

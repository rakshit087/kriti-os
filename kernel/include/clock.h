#ifndef _CLOCK_H
#define _CLOCK_H

#include "ports.h"
#include "isr.h"
#include "mem.h"

typedef struct time_t
{
    uint8 second;
    uint8 minute;
    uint8 hour;
    uint8 day_of_week;
    uint8 day_of_month;
    uint8 month;
    uint8 year;
}time_t;

/*
  The function reads the current time from the Real Time Clock
  to the time_t parameter.

  Input:
    time - A pointer to the time object to read the time to.
*/
void gettime(time_t* time);

/*
  The function initializes the Real Time Clock chip and adding it's handler to the IDT.

  Input:
    None.
  Output:
    None.
*/
void init_clock();

#endif

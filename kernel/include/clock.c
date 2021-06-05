#include "clock.h"

time_t global_time;
int32 bcd;

/*
  The function reads the current time from the Real Time Clock
  to the time_t parameter.

  Input:
    time - A pointer to the time object to read the time to.
  Output:
    None.
*/
void gettime(time_t *time)
{
    memory_copy((int8*)&global_time, (int8*)time, sizeof(time_t));
}

/*
  The handler of the Real Time Clock interrupt, which updates the time global variable
  according to the clock.

  Input:
    The interrupt's coller's registers.
  Output:
    None.
*/
void rtc_handler(registers32_t* r)
{
    if(read_register(0x0C) & 0x10)
    {
        if(bcd)
        {
            global_time.second = bcd2bin(read_register(0x00));
            global_time.minute = bcd2bin(read_register(0x02));
            global_time.hour   = bcd2bin(read_register(0x04));
            global_time.month  = bcd2bin(read_register(0x08));
            global_time.year   = bcd2bin(read_register(0x09));
            global_time.day_of_week  = bcd2bin(read_register(0x06));
            global_time.day_of_month = bcd2bin(read_register(0x07));
        }
        else
        {
            global_time.second = read_register(0x00);
            global_time.minute = read_register(0x02);
            global_time.hour   = read_register(0x04);
            global_time.month  = read_register(0x08);
            global_time.year   = read_register(0x09);
            global_time.day_of_week  = read_register(0x06);
            global_time.day_of_month = read_register(0x07);
        }
    }
}

/*
  The function initializes the Real Time Clock chip and adds it's handler to the IDT.

  Input:
    None.
  Output:
    None.
*/
void init_clock()
{
    uint8 status;

    status = read_register(0x0B);
    status |=  0x02;             // 24 hour clock
    status |=  0x10;             // update ended interrupts
    status &= ~0x20;             // no alarm interrupts
    status &= ~0x40;             // no periodic interrupt
    bcd     =  !(status & 0x04); // check if data type is BCD
    write_register(0x0B, status);

    read_register(0x0C);

    register_interrupt_handler(40, (void*)rtc_handler);
}

#include "timer.h"
uint32 tick=0;

static void timer_callback(registers32_t regs) {
    tick++;
    display("Tick: ",YELLOW);
    char tick_ascii[256];
    int_to_ascii(tick, tick_ascii);
    display(tick_ascii,PINK);
    display("\n",WHITE);
}

// Firstly, register our timer callback.
void init_timer(uint32 frequency)
{
// The value we send to the PIT is the value to divide it's input clock
// (1193180 Hz) by, to get our required frequency. Important to note is
   register_interrupt_handler(TIMER_IRQ, (interrupt_handler_t)&timer_callback);
   uint32 divisor = 1193182 / frequency;
// Send the command byte.
   outb(0x43, 0x36);
// Divisor has to be sent byte-wise, so split here into upper/lower bytes.
   uint8 l = (uint8)(divisor & 0xFF);
   uint8 h = (uint8)((divisor>>8) & 0xFF);
// Send the frequency divisor.
   outb(0x40, l);
   outb(0x40, h);
}

void sleep()
{
  for (uint32 i = 0; i < 10000000; i++){}
}
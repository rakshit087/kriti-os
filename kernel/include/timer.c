#include "timer.h"
#include "display.h"
#include "string.h"
#include "ports.h"
#include "isr.h"

unsigned int tick = 0;

static void timer_callback(registers_t regs) {
    tick++;
    display("Tick: ",WHITE);
    
    char tick_ascii[256];
    int_to_ascii(tick, tick_ascii);
    display(tick_ascii,PINK);
    display("\n",WHITE);
}

void init_timer(unsigned int freq) {
    //Handle the 32th Interrupt (IRQ)
    register_interrupt_handler(IRQ0, timer_callback);

    /* Get the PIT value: hardware clock at 1193180 Hz */
    unsigned int divisor = 1193180 / freq;
    unsigned char low  = (unsigned char)(divisor & 0xFF);
    unsigned char high = (unsigned char)( (divisor >> 8) & 0xFF);
    /* Send the command */
    outb(0x43, 0x36); /* Command port */
    outb(0x40, low);
    outb(0x40, high);
}

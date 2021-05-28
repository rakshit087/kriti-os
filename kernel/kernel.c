#include "include/display.h"
#include "include/isr.h"
#include "include/timer.h"
int kernel_main()
{
    cls();
    display("Welcome to ", YELLOW);
    display("Kriti OS\n\n", PINK);
    init_idt();
    asm volatile("int $0");
    asm volatile("sti");
    init_timer(50);
    return 0;
}

#include "drivers/display.h"

int kernel_main()
{
    cls();
    display("Welcome to ",YELLOW);
    display("Kriti OS\n",PINK);
    return 0;
}
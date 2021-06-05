#include "include/display.h"
#include "include/isr.h"
#include "include/timer.h"
#include "include/keyboard.h"
#include "include/sound.h"
#include "include/clock.h"
#include "include/string.h"
#include "include/graphic.h"
#include "include/mouse.h"
void menu()
{
    cls();
    display("\nWelcome to\n\n", YELLOW);
    display(" | |/ /_ __(_) |_(_)  / _ \\/ ___|\n", PINK);
    display(" | ' /| '__| | __| | | | | \\___ \\ \n", PINK);
    display(" | . \\| |  | | |_| | | |_| |___) |\n", PINK);
    display(" |_|\\_\\_|  |_|\\__|_|  \\___/|____/\n\n", PINK);
    int exitFlag = 1;
    char currStr[200] = {0};
    char currCommand[10] = {0};
    play_on_boot();
    while (exitFlag)
    {
        int i = 0;
        for (uint32 k = 0; k < 10; k++)
        {
            currCommand[k] = 0;
        }

        for (int k = 0; k < 200; k++)
        {
            currStr[k] = 0;
        }

        display("\n>> ", PINK);
        readStr(currStr);
        while (i < 10 && currStr[i] != '\0' && currStr[i] != ' ' && currStr[i] != '\n')
        {
            currCommand[i] = currStr[i];
            i++;
        }
        i++;
        currCommand[i] = 0;

        if (strcmp(currCommand, "exit") == 0) // Exit From The Operating System
        {
            display("\nGoodbye!\n", RED);
            exitFlag = 0;
        }

        if (strcmp(currCommand, "clear") == 0)
        {
            cls();
        }

        if (strcmp(currCommand, "play") == 0)
        {
            play_on_boot();
        }

        if (strcmp(currCommand, "time") == 0)
        {
            {
                time_t currTime;
                char displayMe[20] = {0};
                gettime(&currTime);

                display("\n", PINK);

                switch (currTime.day_of_week)
                {
                case 1:
                    display("Sunday, ", PINK);
                    break;
                case 2:
                    display("Monday, ", PINK);
                    break;
                case 3:
                    display("Tuesday, ", PINK);
                    break;
                case 4:
                    display("Wednesday, ", PINK);
                    break;
                case 5:
                    display("Thursday, ", PINK);
                    break;
                case 6:
                    display("Friday, ", PINK);
                    break;
                case 7:
                    display("Saturday, ", PINK);
                    break;
                }

                int_to_ascii(currTime.day_of_month, displayMe);
                display(displayMe, PINK);

                display("/", PINK);
                int_to_ascii(currTime.month, displayMe);
                display(displayMe, PINK);

                display("/", PINK);
                int_to_ascii(currTime.year, displayMe);
                display(displayMe, PINK);
                display("\n\n", PINK);

                int_to_ascii(currTime.hour, displayMe);
                display(displayMe, PINK);

                display(":", PINK);
                int_to_ascii(currTime.minute, displayMe);
                display(displayMe, PINK);

                display(":", PINK);
                int_to_ascii(currTime.second, displayMe);
                display(displayMe, PINK);
                display("\n", PINK);
            }
        }

        if (strcmp(currCommand, "graphic") == 0) // Exit From The Operating System
        {
            init_mouse();
            display("\nMouse initialized\n\n", PINK);

            registers16_t regs;
            regs.ax = 0x0013;
            rint32(0x10, &regs);

            while (1)
            {
                mouse_handler();
            }
        }

        if (strcmp(currCommand, "help") == 0) // Exit From The Operating System
        {
            display("\n\nexit                          - Exit From The Operating System\n", YELLOW);
            display("help                            - Shows This Help Screen\n", YELLOW);
            display("clear                           - Clear The Screen\n", YELLOW);
            display("graphic                         - Turn On the Graphic Mode\n", YELLOW);
            display("play                            - Play The Melody\n", YELLOW);
        }
    }
}

void kernel_main()
{
    cls();
    isr_install();
    display("IDT initialized\n\n", YELLOW);
    asm volatile("sti");
    init_timer(50);
    display("Timer initialized\n\n", YELLOW);
    init_clock();
    display("Clock initialized\n\n", YELLOW);
    menu();
}

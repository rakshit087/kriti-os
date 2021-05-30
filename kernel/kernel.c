#include "include/display.h"
#include "include/isr.h"
#include "include/timer.h"
#include "include/keyboard.h"
#include "include/sound.h"

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

        if (strcmp(currCommand, "clear") == 0) // Exit From The Operating System
        {
            cls();
        }

        if (strcmp(currCommand, "play") == 0) // Exit From The Operating System
        {
            play_on_boot();
        }

        else
        {
            display("\nEnter Valid Command or Press help for help\n", RED);
        }
    }
}

void kernel_main()
{
    isr_install();
    display("IDT initialized\n\n", YELLOW);
    asm volatile("sti");
    init_timer(50);
    display("Timer initialized\n\n", YELLOW);
    menu();
}

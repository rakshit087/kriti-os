//Reference - https://wiki.osdev.org/%228042%22_PS/2_Controller
#include "keyboard.h"

char readChar()
{
	char buffstr[2] = {0};
	uint8 i = 0;
	uint8 reading = 1;
	while (reading && buffstr[0] == 0)
	{
		if (inb(0x64) & 0x1) //If key is pressed
		{
			switch (inb(0x60)) //Read the 0x60 port which gives scan code
			{
			// case 1:
			// displaackspace();
			//         i--;
			//         break;
			case 2:
				display("1", CYAN);
				buffstr[i] = '1';
				i++;
				break;
			case 3:
				display("2", CYAN);
				buffstr[i] = '2';
				i++;
				break;
			case 4:
				display("3", CYAN);
				buffstr[i] = '3';
				i++;
				break;
			case 5:
				display("4", CYAN);
				buffstr[i] = '4';
				i++;
				break;
			case 6:
				display("5", CYAN);
				buffstr[i] = '5';
				i++;
				break;
			case 7:
				display("6", CYAN);
				buffstr[i] = '6';
				i++;
				break;
			case 8:
				display("7", CYAN);
				buffstr[i] = '7';
				i++;
				break;
			case 9:
				display("8", CYAN);
				buffstr[i] = '8';
				i++;
				break;
			case 10:
				display("9", CYAN);
				buffstr[i] = '9';
				i++;
				break;
			case 11:
				display("0", CYAN);
				buffstr[i] = '0';
				i++;
				break;
			case 12:
				display("-", CYAN);
				buffstr[i] = '-';
				i++;
				break;
			case 13:
				display("=", CYAN);
				buffstr[i] = '=';
				i++;
				break;
			case 14:
				buffstr[i] = '\b'; //BACKSPACE
				break;
				/* case 15:
              display('\t');          Tab button
              buffstr[i] = '\t';
              i++;
              break;*/
			case 16:
				display("q", CYAN);
				buffstr[i] = 'q';
				i++;
				break;
			case 17:
				display("w", CYAN);
				buffstr[i] = 'w';
				i++;
				break;
			case 18:
				display("e", CYAN);
				buffstr[i] = 'e';
				i++;
				break;
			case 19:
				display("r", CYAN);
				buffstr[i] = 'r';
				i++;
				break;
			case 20:
				display("t", CYAN);
				buffstr[i] = 't';
				i++;
				break;
			case 21:
				display("y", CYAN);
				buffstr[i] = 'y';
				i++;
				break;
			case 22:
				display("u", CYAN);
				buffstr[i] = 'u';
				i++;
				break;
			case 23:
				display("i", CYAN);
				buffstr[i] = 'i';
				i++;
				break;
			case 24:
				display("o", CYAN);
				buffstr[i] = 'o';
				i++;
				break;
			case 25:
				display("p", CYAN);
				buffstr[i] = 'p';
				i++;
				break;
			case 26:
				display("[", CYAN);
				buffstr[i] = '[';
				i++;
				break;
			case 27:
				display("]", CYAN);
				buffstr[i] = ']';
				i++;
				break;
			case 28:
				//display('\n');
				buffstr[i] = '\n';
				i++;
				reading = 0;
				break;
			case 29:
				// if (i > 0)
				// {
				//         display_backspace();
				//         buffstr[i] = '\0';
				//         i--;
				// }

				break;
			case 30:
				display("a", CYAN);
				buffstr[i] = 'a';
				i++;
				break;
			case 31:
				display("s", CYAN);
				buffstr[i] = 's';
				i++;
				break;
			case 32:
				display("d", CYAN);
				buffstr[i] = 'd';
				i++;
				break;
			case 33:
				display("f", CYAN);
				buffstr[i] = 'f';
				i++;
				break;
			case 34:
				display("g", CYAN);
				buffstr[i] = 'g';
				i++;
				break;
			case 35:
				display("h", CYAN);
				buffstr[i] = 'h';
				i++;
				break;
			case 36:
				display("j", CYAN);
				buffstr[i] = 'j';
				i++;
				break;
			case 37:
				display("k", CYAN);
				buffstr[i] = 'k';
				i++;
				break;
			case 38:
				display("l", CYAN);
				buffstr[i] = 'l';
				i++;
				break;
			case 39:
				display(";", CYAN);
				buffstr[i] = ';';
				i++;
				break;
			case 40:
				display("\'", CYAN); //   Single quote (')
				buffstr[i] = '\'';
				i++;
				break;
			case 41:
				display("`", CYAN); // Back tick (`)
				buffstr[i] = '`';
				i++;
				break;
				/* case 42:                                 Left shift
              display('q');
              buffstr[i] = 'q';
              i++;
              break;
      case 43:                                 \ (< for somekeyboards)
              display((char)92);
              buffstr[i] = 'q';
              i++;
              break;*/
			case 44:
				display("z", CYAN);
				buffstr[i] = 'z';
				i++;
				break;
			case 45:
				display("x", CYAN);
				buffstr[i] = 'x';
				i++;
				break;
			case 46:
				display("c", CYAN);
				buffstr[i] = 'c';
				i++;
				break;
			case 47:
				display("v", CYAN);
				buffstr[i] = 'v';
				i++;
				break;
			case 48:
				display("b", CYAN);
				buffstr[i] = 'b';
				i++;
				break;
			case 49:
				display("n", CYAN);
				buffstr[i] = 'n';
				i++;
				break;
			case 50:
				display("m", CYAN);
				buffstr[i] = 'm';
				i++;
				break;
			case 51:
				display(",", CYAN);
				buffstr[i] = ',';
				i++;
				break;
			case 52:
				display(".", CYAN);
				buffstr[i] = '.';
				i++;
				break;
			case 53:
				display("/", CYAN);
				buffstr[i] = '/';
				i++;
				break;
			case 54:
				display(".", CYAN);
				buffstr[i] = '.';
				i++;
				break;
			case 55:
				display("/", CYAN);
				buffstr[i] = '/';
				i++;
				break;
				/*case 56:
              display(' ');           Right shift
              buffstr[i] = ' ';
              i++;
              break;*/
			case 57:
				display(" ", CYAN);
				buffstr[i] = ' ';
				i++;
				break;
			}
		}
	}

	return buffstr[0];
}

/*
  The function reads a string from the keyboard.

  Input:
    A pointer to the string to read to .
  Output:
    None.
*/
void readStr(char *buffstr)
{
	char buff;
	uint8 i = 0;
	uint8 reading = 1;
	while (reading)
	{
		buffstr[i] = readChar();
		if (buffstr[i] == '\b')
		{
			if (i > 0)
			{
				display_backspace();
				i--;
			}
		}
		else
		{
			if (buffstr[i] == '\n')
			{
				reading = 0;
			}
			i++;
		}
	}
	buffstr[i - 1] = 0;
}

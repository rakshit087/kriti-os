// Reference - https://wiki.osdev.org/PC_Speaker#Through_the_Programmable_Interval_Timer_.28PIT.29
#include "sound.h"

static void play_sound(uint32 nFrequence)
{
	int scale;
	if (nFrequence == 0)
	{
		outb(0x61, inb(0x61) & ~3);
		return;
	}
	scale = 1193046 / nFrequence;
	outb(0x43, 0xb6);
	outb(0x42, scale & 0xff);
	outb(0x42, scale >> 8);
	outb(0x61, inb(0x61) | 3);
}

static void nosound()
{
	uint8 tmp = inb(0x61) & 0xFC;

	outb(0x61, tmp);
}

void beep(uint32 nFrequence)
{
	play_sound(nFrequence);
	sleep();
	nosound();
}
void play_on_boot()
{
	//Chord-> A B E+A B E+D+C#+
	beep(277); //C#
	sleep();
	beep(293); //D
	sleep();
	beep(329); //E
	sleep();
	beep(440); //A
	beep(440); //A
	beep(440); //A
	sleep();sleep();sleep();sleep();sleep();
	beep(440); //A
	sleep();
	beep(493); //B
	sleep();
	beep(415); //G#
	sleep();
	beep(580); //E5
	beep(580); //E5
	beep(580); //E5
	sleep();sleep();sleep();sleep();sleep();sleep();
	beep(440); //A
	sleep();
	beep(493); //B
	sleep();
	beep(620); //E
	sleep();
	beep(586); //D
	beep(586); //D
	sleep();
	beep(415); //G#
	sleep();
}
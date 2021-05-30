#ifndef SOUND_H
#define SOUND_H

#include "ports.h"
#include "types.h"
#include "timer.h"
static void play_sound(uint32 nFrequence);
static void nosound();
void beep(uint32 nFrequence);
void play_on_boot();
#endif
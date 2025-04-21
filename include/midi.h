// include/midi.h
#pragma once
#include <windows.h>
#include "mixer.h"

typedef void (*MIDI_Callback)(Mixer *, BYTE, BYTE, BYTE);

int midi_init(MIDI_Callback callback, Mixer *mixer);
void midi_close();
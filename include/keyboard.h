
#pragma once
#include "midi.h"

void keyboard_init(MidiCallback callback, void *user);
void keyboard_close();
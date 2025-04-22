#pragma once
#include "synth.h"

typedef struct Mixer
{
    Synth **synths;
    int count;
    int capacity;
    float master_vol;
} Mixer;

Mixer *mixer_create();
void mixer_free(Mixer *mixer);
void mixer_add(Mixer *mixer, Synth *synth);
short mixer_process(Mixer *mixer, double sr);
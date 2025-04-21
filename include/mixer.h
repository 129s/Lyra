#pragma once
#include "wave_generator.h"

typedef struct Mixer
{
    WaveGenerator **generators;
    int count;
    int capacity;
    float master_volume;
} Mixer;

Mixer *mixer_create();
void mixer_destroy(Mixer *mixer);
void mixer_add(Mixer *mixer, WaveGenerator *gen);
short mixer_process(Mixer *mixer, double sample_rate);
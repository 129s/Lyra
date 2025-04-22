#include "mixer.h"
#include <stdlib.h>
#include <math.h>

Mixer *mixer_create()
{
    Mixer *m = malloc(sizeof(Mixer));
    m->capacity = 8;
    m->synths = malloc(m->capacity * sizeof(Synth *));
    m->count = 0;
    m->master_vol = 1.0f;
    return m;
}

void mixer_free(Mixer *mixer)
{
    if (!mixer)
        return;
    free(mixer->synths);
    free(mixer);
}

void mixer_add(Mixer *mixer, Synth *synth)
{
    if (mixer->count >= mixer->capacity)
    {
        mixer->capacity *= 2;
        mixer->synths = realloc(mixer->synths,
                                mixer->capacity * sizeof(Synth *));
    }
    mixer->synths[mixer->count++] = synth;
}

short mixer_process(Mixer *mixer, double sr)
{
    float mix = 0.0f;
    for (int i = 0; i < mixer->count; i++)
    {
        mix += synth_process(mixer->synths[i], sr);
    }
    mix = fmaxf(fminf(mix * mixer->master_vol, 32767), -32768);
    return (short)mix;
}
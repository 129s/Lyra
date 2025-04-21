#include "mixer.h"
#include <stdlib.h>

Mixer *mixer_create()
{
    Mixer *mixer = malloc(sizeof(Mixer));
    mixer->generators = malloc(sizeof(WaveGenerator *) * 8); // 初始容量8
    mixer->count = 0;
    mixer->capacity = 8;
    mixer->master_volume = 1.0f;
    return mixer;
}

void mixer_destroy(Mixer *mixer)
{
    free(mixer->generators);
    free(mixer);
}

void mixer_add(Mixer *mixer, WaveGenerator *gen)
{
    if (mixer->count >= mixer->capacity)
    {
        mixer->capacity *= 2;
        mixer->generators = realloc(mixer->generators, sizeof(WaveGenerator *) * mixer->capacity);
    }
    mixer->generators[mixer->count++] = gen;
}

short mixer_process(Mixer *mixer, double sample_rate)
{
    float mixed = 0.0f;
    for (int i = 0; i < mixer->count; ++i)
    {
        mixed += wave_next(mixer->generators[i], sample_rate);
    }
    mixed *= mixer->master_volume;

    // 限制输出范围
    if (mixed > 32767)
        mixed = 32767;
    if (mixed < -32768)
        mixed = -32768;
    return (short)mixed;
}
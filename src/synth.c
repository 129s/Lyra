#include "synth.h"
#include <math.h>
#include <stdlib.h>

static float midi_to_freq(uint8_t note)
{
    return 440.0f * powf(2.0f, (note - 69) / 12.0f);
}

void synth_init(Synth *synth)
{
    for (int i = 0; i < MAX_VOICES; i++)
    {
        synth->voices[i] = (Voice){0};
    }
    synth->default_wave = WAVE_SINE;
    synth->default_amp = 30000;
    synth->master_vol = 1.0f;
}

void synth_midi_in(Synth *synth, const uint8_t *msg)
{
    uint8_t status = msg[0] & 0xF0;
    uint8_t note = msg[1];
    uint8_t vel = msg[2];

    switch (status)
    {
    case 0x90: // Note On
        if (vel > 0)
        {
            // Voice分配策略：优先复用相同音符
            int target = -1;
            for (int i = 0; i < MAX_VOICES; i++)
            {
                if (synth->voices[i].note == note)
                {
                    target = i;
                    break;
                }
                if (target == -1 && !synth->voices[i].active)
                    target = i;
            }
            if (target == -1)
                target = rand() % MAX_VOICES; // 随机置换

            synth->voices[target] = (Voice){
                .active = true,
                .frequency = midi_to_freq(note),
                .amplitude = (vel * synth->default_amp) / 127,
                .wave_type = synth->default_wave,
                .phase = 0,
                .note = note};
        }
        break;

    case 0x80: // Note Off
        for (int i = 0; i < MAX_VOICES; i++)
        {
            if (synth->voices[i].note == note)
            {
                synth->voices[i].active = false;
            }
        }
        break;
    }
}

short synth_process(Synth *synth, double sr)
{
    float mix = 0.0f;
    const double dt = 1.0 / sr;

    for (int i = 0; i < MAX_VOICES; i++)
    {
        Voice *v = &synth->voices[i];
        if (!v->active)
            continue;

        double pos = v->phase;
        short sample = 0;

        switch (v->wave_type)
        {
        case WAVE_SINE:
            sample = v->amplitude * sin(2 * M_PI * pos);
            break;

        case WAVE_SQUARE:
            sample = (fmod(pos, 1.0) < 0.5) ? v->amplitude : -v->amplitude;
            break;

        case WAVE_SAWTOOTH:
            sample = 2 * v->amplitude * (pos - floor(pos) - 0.5);
            break;

        case WAVE_TRIANGLE:
        {
            double x = 2 * fmod(pos, 1.0);
            sample = v->amplitude * (x < 1.0 ? 2 * x - 1 : 3 - 2 * x);
            break;
        }
        }

        mix += sample;
        v->phase += v->frequency * dt;
        if (v->phase >= 1.0)
            v->phase -= 1.0;
    }

    // 限制输出并应用主音量
    mix = fmaxf(fminf(mix * synth->master_vol, 32767), -32768);
    return (short)mix;
}
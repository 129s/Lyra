#include "synth.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

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
    synth->default_wave = WAVE_SQUARE;
    synth->default_amp = 32767 / MAX_VOICES;
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
        if (vel == 0)
        { // 处理力度为0的Note On视为Note Off
            for (int j = 0; j < MAX_VOICES; j++)
            {
                Voice *v = &synth->voices[j];
                if (v->active && v->note == note)
                {
                    v->active = false;
                }
            }
            break;
        }
        // 寻找空闲的语音通道
        for (int j = 0; j < MAX_VOICES; j++)
        {
            Voice *v = &synth->voices[j];
            if (!v->active)
            {
                v->active = true;
                v->note = note;
                v->frequency = midi_to_freq(note);
                v->amplitude = (int)((vel / 127.0f) * synth->default_amp);
                v->wave_type = synth->default_wave;
                break;
            }
        }
        break;

    case 0x80: // Note Off
        for (int j = 0; j < MAX_VOICES; j++)
        {
            Voice *v = &synth->voices[j];
            if (v->active && v->note == note)
            {
                v->active = false;
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

        float amp = v->amplitude;

        // 波形生成逻辑
        double pos = v->phase;
        short sample = 0;

        switch (v->wave_type)
        {
        case WAVE_SINE:
            sample = amp * sin(2 * M_PI * pos);
            break;

        case WAVE_SQUARE:
            sample = (fmod(pos, 1.0) < 0.5) ? amp : -amp;
            break;

        case WAVE_SAWTOOTH:
            sample = 2 * amp * (pos - floor(pos) - 0.5);
            break;

        case WAVE_TRIANGLE:
        {
            double x = 2 * fmod(pos, 1.0);
            sample = amp * (x < 1.0 ? 2 * x - 1 : 3 - 2 * x);
            break;
        }
        }
        mix += sample;
        v->phase += v->frequency * dt;
        if (v->phase >= 1.0)
            v->phase -= 1.0;
    }

    // 削波处理
    return (short)fmaxf(fminf(mix * synth->master_vol, 32767), -32768);
}
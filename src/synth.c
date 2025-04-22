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
    synth->default_amp = 19684;
    synth->master_vol = 1.0f;
    synth->active_voices = 0;
    synth->auto_volume = true;
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
            // 查找现有相同音符的voice或空闲voice
            int target = -1;
            for (int i = 0; i < MAX_VOICES; i++)
            {
                if (synth->voices[i].note == note && synth->voices[i].active)
                {
                    target = i;
                    break;
                }
            }
            if (target == -1)
            {
                // 寻找空闲voice
                for (int i = 0; i < MAX_VOICES; i++)
                {
                    if (!synth->voices[i].active)
                    {
                        target = i;
                        break;
                    }
                }
            }
            if (target == -1)
            {
                // 随机替换
                target = rand() % MAX_VOICES;
                if (synth->voices[target].active)
                    synth->active_voices--;
            }

            // 保留相位（如果复用现有voice）
            double phase = (target != -1 && synth->voices[target].active) ? synth->voices[target].phase : 0.0;

            synth->voices[target] = (Voice){
                .active = true,
                .frequency = midi_to_freq(note),
                .amplitude = (vel * synth->default_amp) / 127,
                .wave_type = synth->default_wave,
                .phase = phase, // 保留相位
                .note = note};

            if (!synth->voices[target].active)
                synth->active_voices++;
        }
        break;

    case 0x80: // Note Off
        for (int i = 0; i < MAX_VOICES; i++)
        {
            if (synth->voices[i].note == note)
            {
                synth->voices[i].active = false;
                synth->active_voices--;
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

        // 根据 auto_volume 调整振幅
        float amp = v->amplitude;
        if (synth->auto_volume && synth->active_voices > 0)
        {
            amp /= synth->active_voices;
            printf("%f\n", amp);
        }

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
        // 相位更新
        v->phase += v->frequency * dt;
        if (v->phase >= 1.0)
            v->phase -= 1.0;
    }

    // 削波输出
    mix = fmaxf(fminf(mix * synth->master_vol, 32767), -32768);
    return (short)mix;
}
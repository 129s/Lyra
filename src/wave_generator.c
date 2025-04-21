#define _USE_MATH_DEFINES
#include <math.h>
#include "wave_generator.h"

void wave_init(WaveGenerator *gen, WaveType type, float freq, int amp)
{
    gen->wave_type = type;
    gen->frequency = freq;
    gen->amplitude = amp;
    gen->phase = 0.0;
}
short wave_next(WaveGenerator *gen, double sample_rate)
{
    const double period = 1.0 / gen->frequency;
    const double phase_step = gen->frequency / sample_rate;
    double pos = gen->phase;

    short sample;
    switch (gen->wave_type)
    {
    case WAVE_SINE:
        sample = gen->amplitude * sin(2 * M_PI * pos);
        break;
    case WAVE_SQUARE:
        sample = (fmod(pos, 1.0) < 0.5) ? gen->amplitude : -gen->amplitude;
        break;
    case WAVE_SAWTOOTH:
        sample = 2 * gen->amplitude * (pos - floor(pos) - 0.5);
        break;
    case WAVE_TRIANGLE:
        sample = gen->amplitude * (2 * fabs(2 * (pos - floor(pos)) - 1) - 1);
        break;
    default:
        sample = 0;
    }

    gen->phase += phase_step;
    if (gen->phase >= 1.0)
        gen->phase -= 1.0;

    return sample;
}

void wave_trigger(WaveGenerator *gen, bool on)
{
    gen->active = on;
    if (!on)
        gen->phase = 0.0; // 停止时重置相位
}
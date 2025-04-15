
#include "sine_wave.h"
#include <cmath>
#define M_PI 3.14159265358979323846

SineWaveProcessor::SineWaveProcessor(int sampleRate, int blockSize)
    : sampleRate_(sampleRate), blockSize_(blockSize)
{
}

void SineWaveProcessor::ProcessMidiEvent(const VstMidiEvent &event)
{
    const byte status = event.midiData[0] & 0xF0;
    const byte note = event.midiData[1];
    const byte velocity = event.midiData[2];

    if (status == 0x90 && velocity > 0)
    { // Note On
        frequency_ = 440.0 * pow(2.0, (note - 69) / 12.0);
        amplitude_ = velocity / 127.0;
    }
    else if (status == 0x80 || (status == 0x90 && velocity == 0))
    { // Note Off
        amplitude_ = 0.0;
    }
}

bool SineWaveProcessor::ProcessAudio(float *left, float *right, int numSamples)
{
    const double phaseIncrement = 2.0 * M_PI * frequency_ / sampleRate_;

    for (int i = 0; i < numSamples; ++i)
    {
        const double sample = amplitude_ * sin(phase_);
        left[i] = sample;
        right[i] = sample;

        phase_ += phaseIncrement;
        if (phase_ >= 2.0 * M_PI)
            phase_ -= 2.0 * M_PI;
    }
    return true;
}

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

    // Note On
    if (status == 0x90 && velocity > 0)
    {
        envelope_stage_ = kAttack;
        envelope_pos_ = 0;
        frequency_ = 440.0 * pow(2.0, (note - 69) / 12.0);
        max_amplitude_ = velocity % 127 / 127.0f;
    }
    // Note Off
    else if (status == 0x80 || (status == 0x90 && velocity == 0))
    {
        envelope_stage_ = kRelease;
        envelope_pos_ = 0;
    }
}
bool SineWaveProcessor::ProcessAudio(float *left, float *right, int numSamples)
{
    const double phaseIncrement = 2.0 * M_PI * frequency_ / sampleRate_;

    for (int i = 0; i < numSamples; ++i)
    {
        // 处理包络状态
        switch (envelope_stage_)
        {
        case kAttack:
            amplitude_ = std::min(static_cast<double>(envelope_pos_) / attack_samples_, max_amplitude_);
            if (++envelope_pos_ >= attack_samples_)
                envelope_stage_ = kIdle;
            break;

        case kRelease:
            amplitude_ = std::max(max_amplitude_ - static_cast<double>(envelope_pos_) / release_samples_, 0.0);
            if (++envelope_pos_ >= release_samples_)
            {
                envelope_stage_ = kIdle;
                amplitude_ = 0.0;
            }
            break;

        case kIdle:
            break;
        }

        // 生成正弦波
        const double sample = amplitude_ * sin(phase_);
        left[i] = sample;
        right[i] = sample;

        phase_ += phaseIncrement;
        if (phase_ >= 2.0 * M_PI)
            phase_ -= 2.0 * M_PI;
    }

    return true;
}
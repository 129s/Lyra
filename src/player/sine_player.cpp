
#include "player/sine_player.h"
#include <cmath>

SinePlayer::SinePlayer(int sampleRate)
    : sampleRate_(sampleRate), phaseIncrement_(2.0 * M_PI / sampleRate) {}

void SinePlayer::ProcessMidiEvents(const std::vector<MidiEvent> &events)
{
    for (const auto &event : events)
    {
        if (event.type == MidiEvent::NoteOn)
        {
            Voice &v = voices_[event.pitch];
            v.frequency = 440.0 * pow(2.0, (event.pitch - 69) / 12.0);
            v.amplitude = event.velocity / 127.0;
            v.active = true;
        }
        else if (event.type == MidiEvent::NoteOff)
        {
            auto it = voices_.find(event.pitch);
            if (it != voices_.end())
                it->second.active = false;
        }
    }
}

bool SinePlayer::RenderAudio(float *left, float *right, int numSamples)
{
    bool hasOutput = false;

    for (int i = 0; i < numSamples; ++i)
    {
        float sample = 0.0f;
        for (auto &[pitch, voice] : voices_)
        {
            if (!voice.active)
                continue;

            sample += static_cast<float>(sin(voice.phase) * voice.amplitude);
            voice.phase += voice.frequency * phaseIncrement_;
            if (voice.phase > 2 * M_PI)
                voice.phase -= 2 * M_PI;

            hasOutput = true;
        }
        left[i] = sample;
        right[i] = sample;
    }

    return hasOutput;
}

void SinePlayer::Reset() { voices_.clear(); }
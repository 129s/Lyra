
#pragma once
#include "core/player.h"
#include <vector>
#include <map>

class SinePlayer : public Player
{
public:
    SinePlayer(int sampleRate);
    void ProcessMidiEvents(const std::vector<MidiEvent> &events) override;
    bool RenderAudio(float *left, float *right, int numSamples) override;
    void Reset() override;

private:
    struct Voice
    {
        double phase = 0.0;
        double frequency = 0.0;
        double amplitude = 0.0;
        bool active = false;
    };

    std::map<int, Voice> voices_; // 按音符编号索引
    const int sampleRate_;
    const double phaseIncrement_;
};
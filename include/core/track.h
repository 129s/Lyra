
#pragma once
#include "timeline.h"
#include "player.h"
#include <memory>

class Track
{
public:
    Track(std::unique_ptr<Player> player);

    // 音频生成入口
    void RenderAudio(float *left, float *right, int numSamples);

    // 时间轴控制
    void Play() { timeline_.Play(); }
    void Stop()
    {
        timeline_.Stop();
        player_->Reset();
    }

    void ProcessMidi(std::vector<MidiEvent> &events);

    Timeline &GetTimeline() { return timeline_; }

private:
    Timeline timeline_;
    std::unique_ptr<Player> player_;
};

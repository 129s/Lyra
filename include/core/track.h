
#pragma once
#include "timeline.h"
#include "player.h"
#include <memory>
class Track
{
public:
    void AddClip(const MidiClip &clip);
    void RenderAudio(float *left, float *right, int numSamples);

    void BindPlayer(std::unique_ptr<Player> player)
    {
        player_ = std::move(player);
    }

private:
    std::vector<MidiClip> clips_;
    std::unique_ptr<Player> player_;
    double timeOffset_ = 0.0; // 轨道级时间偏移
};
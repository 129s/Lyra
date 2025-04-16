
#pragma once
#include "timeline.h"
#include "player.h"
#include <memory>
class Track
{
public:
    Track() = default;

    // 显式声明移动语义
    Track(Track &&) = default;
    Track &operator=(Track &&) = default;

    ~Track();

    void AddClip(const MidiClip &clip);
    void RenderAudio(float *left, float *right, int numSamples);

    Player *GetPlayer() const { return player_.get(); }
    void BindPlayer(std::unique_ptr<Player> player)
    {
        player_ = std::move(player);
    }

private:
    std::vector<MidiClip> clips_;
    std::unique_ptr<Player> player_;
    double timeOffset_ = 0.0; // 轨道级时间偏移
};
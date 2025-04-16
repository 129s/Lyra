
#pragma once
#include "timeline.h"
#include "mixer.h"
#include <unordered_map>

class Controller
{
public:
    Controller();
    ~Controller();
    void Update(double deltaTime); // 由音频回调驱动

    Timeline &GetTimeline() { return timeline_; }

    // 全局传输控制
    void Play() { timeline_.SetPlayState(true); }
    void Stop()
    {
        timeline_.SetGlobalTime(0.0);
        timeline_.SetPlayState(false);
    }

private:
    Timeline timeline_;
    std::unordered_map<int, Player *> trackPlayers_;
    Mixer &mixer_;
};
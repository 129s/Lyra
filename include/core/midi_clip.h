
#pragma once
#include "event.h"
#include <queue>
#include <vector>

class MidiClip
{
public:
    void AddNote(double localTime, const Note &note);
    const std::vector<MidiEvent> &GetEvents(double globalTime) const;

    void SetStartTime(double globalStart);        // 设置全局起始时间
    void SetLoop(bool loop, double duration = 0); // 循环设置

    double GetDuration() const; // 基于最晚事件时间计算

private:
    std::priority_queue<std::pair<double, MidiEvent>> events_;
    double globalStartTime_ = 0.0;
    bool isLooping_ = false;
    double loopDuration_ = 0.0;
};
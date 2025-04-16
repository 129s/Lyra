
#pragma once
#include "event.h"
#include "audio_clock.h"
#include <queue>
#include <functional>

class Timeline
{
public:
    explicit Timeline(AudioClock &clock) : clock_(clock) {}

    // 添加事件时记录全局时间戳
    void ScheduleEvent(const MidiEvent &event, double timestamp);

    // 根据全局时间轮询事件
    std::vector<MidiEvent> PollEvents();

    // 播放/停止逻辑调整为依赖全局时间
    void Play() { isPlaying_ = true; }
    void Stop() { isPlaying_ = false; }
    void Continue();

private:
    AudioClock &clock_;
    std::priority_queue<std::pair<double, MidiEvent>> eventQueue_; // 按时间戳排序
    bool isPlaying_ = false;
};
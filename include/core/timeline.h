
#pragma once
#include "event.h"
#include <queue>
#include <functional>

class Timeline
{
public:
    // 添加事件到时间轴
    void ScheduleEvent(const MidiEvent &event);

    // 播放控制
    void Play();
    void Stop();
    void Continue();

    // 获取当前时间之后需要触发的事件（由Player轮询调用）
    std::vector<MidiEvent> PollEvents(double currentTime);

private:
    std::priority_queue<MidiEvent, std::vector<MidiEvent>,
                        std::function<bool(const MidiEvent &, const MidiEvent &)>>
        eventQueue_;
    bool isPlaying_ = false;
    double playhead_ = 0.0;
};
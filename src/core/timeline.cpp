
#include "core/timeline.h"

void Timeline::AddClip(int trackIdx, MidiClip &&clip, double startTime)
{
    if (trackIdx >= tracks_.size())
        tracks_.resize(trackIdx + 1);
    tracks_[trackIdx].clips.emplace_back(std::move(clip));
    // 这里需要记录clip的开始时间（需扩展数据结构）
}

std::vector<MidiEvent> Timeline::PollEvents(double currentTime)
{
    std::vector<MidiEvent> events;
    if (!isPlaying_)
        return events;

    for (auto &track : tracks_)
    {
        for (auto &clip : track.clips)
        {
            // 根据currentTime和clip的起始时间获取事件
            auto clipEvents = clip.GetEvents(currentTime - track.trackOffset);
            events.insert(events.end(), clipEvents.begin(), clipEvents.end());
        }
    }
    return events;
}
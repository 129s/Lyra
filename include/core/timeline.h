// 文件路径：include/core/timeline.h
#pragma once
#include "midi_clip.h"
#include <vector>

struct TrackState
{
    std::vector<MidiClip> clips;
    bool isMuted = false;
    double trackOffset = 0.0; // 轨道时间偏移
};

class Timeline
{
public:
    void AddClip(int trackIdx, MidiClip &&clip, double startTime);

    // 获取当前激活的MIDI事件（全局时间→局部时间转换）
    std::vector<MidiEvent> PollEvents(double currentTime);

    void SetGlobalTime(double time);
    void SetPlayState(bool isPlaying);

private:
    std::vector<TrackState> tracks_;
    double globalTime_ = 0.0;
    bool isPlaying_ = false;
};

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

    // 根据全局时间轮询midi事件
    std::vector<MidiEvent> PollMidiEvents();

    // 在指定位置添加音符
    void AddNote(double timestamp, const Note &note)
    {
        MidiEvent noteOn;
        noteOn.type = MidiEvent::NoteOn;
        noteOn.timestamp = timestamp; // 事件时间戳
        noteOn.note = note.pitch;
        noteOn.velocity = note.velocity;
        midiEventQueue_.emplace(timestamp, noteOn);

        MidiEvent noteOff;
        noteOff.type = MidiEvent::NoteOff;
        noteOff.timestamp = timestamp + note.duration; // NoteOff 时间戳
        noteOff.note = note.pitch;
        noteOff.velocity = 0; // NoteOff 通常力度为0
        midiEventQueue_.emplace(noteOff.timestamp, noteOff);

        lastEventTime_ = noteOff.timestamp; // 更新末尾时间
    }

    // 在末尾追加音符
    void AppendNote(const Note &note)
    {
        AddNote(lastEventTime_, note);
    }

    // 播放/停止，依赖全局时间
    void Play() { isPlaying_ = true; }
    void Stop() { isPlaying_ = false; }
    void Continue();

private:
    AudioClock &clock_;
    std::priority_queue<std::pair<double, MidiEvent>> midiEventQueue_; // 按时间戳排序
    bool isPlaying_ = false;
    double lastEventTime_ = 0.0; // 记录最后一个事件的结束时间
};
#pragma once
#include <cstdint>

class Event
{
public:
    virtual ~Event() = default;
    virtual void execute() = 0; // 事件触发逻辑
    double timestamp;           // 事件发生时间（秒）
};

struct MidiEvent
{
    enum Type
    {
        NoteOn,
        NoteOff
    };

    Type type;
    int note;     // MIDI音符编号 (0-127)
    int velocity; // 力度 (0-127)
};

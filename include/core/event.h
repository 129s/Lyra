#pragma once
#include <cstdint>

struct Note
{
    int pitch;       // 音高 (MIDI编号 0-127)
    int velocity;    // 力度 (0-127)
    double duration; // 时值（秒）
};

class Event
{
public:
    virtual ~Event() = default;
    virtual void execute() = 0; // 事件触发逻辑
    double timestamp;           // 事件发生时间（秒）
};

struct SystemEvent : public Event
{
    enum Type
    {
        Play,
        Stop
    };
    Type type;
    double timestamp; // 关联全局时间
};

struct MidiEvent : public Event
{
    enum Type
    {
        NoteOn,
        NoteOff
    };

    Type type;
    int pitch;    // MIDI音高编号 (0-127)
    int velocity; // 力度 (0-127)
};

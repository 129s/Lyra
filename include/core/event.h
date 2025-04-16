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
    virtual void execute() = 0;                // 事件触发逻辑
    static constexpr uint32_t EventTypeID = 1; // 唯一类型标识
    double timestamp;                          // 事件发生时间（秒）
};
struct SystemEvent : public Event
{
    void execute() override {}
    enum Type
    {
        Play,
        Stop
    };
    static constexpr uint32_t EventTypeID = 1;
    Type type;
};

struct MidiEvent : public Event
{
    void execute() override {}
    enum Type
    {
        NoteOn,
        NoteOff
    };
    static constexpr uint32_t EventTypeID = 2;
    Type type;
    int pitch;    // MIDI音高编号 (0-127)
    int velocity; // 力度 (0-127)
};

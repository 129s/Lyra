#pragma once
#include "event.h"
#include "vst2.x/aeffectx.h"

class MidiEvent : public Event
{
public:
    MidiEvent(uint64_t tick, const VstMidiEvent &event)
        : tick_(tick), event_(event) {}

    uint64_t get_tick() const override { return tick_; }

    void trigger(uint64_t) override
    {
        // 实际MIDI处理逻辑将在Processor中实现
    }

    bool is_complete(uint64_t current_tick) const override
    {
        return current_tick >= tick_;
    }

    const VstMidiEvent &get_vst_event() const { return event_; }

private:
    uint64_t tick_;
    VstMidiEvent event_;
};
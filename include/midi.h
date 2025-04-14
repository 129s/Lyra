
#pragma once
#include <queue>
#include <mutex>
#include "vst2.x/aeffectx.h"

struct MidiEvent
{
    VstMidiEvent event;
    unsigned int frame_offset;
};

class MidiEventQueue
{
public:
    void Push(const VstMidiEvent &event, unsigned int frame_offset = 0);
    bool Pop(VstMidiEvent &event, unsigned int &frame_offset);
    void Clear();

private:
    std::queue<MidiEvent> queue_;
    std::mutex mutex_;
};
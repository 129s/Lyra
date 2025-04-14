
#include "midi.h"

void MidiEventQueue::Push(const VstMidiEvent &event, unsigned int frame_offset)
{
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.push({event, frame_offset});
}

bool MidiEventQueue::Pop(VstMidiEvent &event, unsigned int &frame_offset)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (queue_.empty())
        return false;
    const auto &item = queue_.front();
    event = item.event;
    frame_offset = item.frame_offset;
    queue_.pop();
    return true;
}

void MidiEventQueue::Clear()
{
    std::lock_guard<std::mutex> lock(mutex_);
    while (!queue_.empty())
        queue_.pop();
}
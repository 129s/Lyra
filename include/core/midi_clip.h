
#pragma once
#include "event.h"
#include <queue>
#include <vector>

class MidiClip
{
public:
    void AddNote(double localTime, const Note &note);
    const std::vector<MidiEvent> &GetEvents(double globalTime) const;

    double GetDuration() const;

private:
    std::priority_queue<std::pair<double, MidiEvent>> events_;
    double duration_ = 0.0;
};
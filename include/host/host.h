
#pragma once
#include "track.h"
#include "core/mixer.h"
#include "audio/audio_output.h"
#include "core/event_bus.h"

class Host
{
public:
    Host() : eventBus_(std::make_unique<EventBus>()),
             mixer_(),
             audioOutput_(std::make_unique<AudioOutput>(mixer_, 44100, 512)),
             audioClock_(std::make_unique<AudioClock>(*audioOutput_)) {}

    EventBus &GetEventBus() { return *eventBus_; }

    Track &CreateTrack(std::unique_ptr<Player> player);
    void RemoveTrack(int index);

    void PlayAll();
    void StopAll();

private:
    std::unique_ptr<EventBus> eventBus_;
    Mixer mixer_;
    std::unique_ptr<AudioOutput> audioOutput_;
    std::unique_ptr<AudioClock> audioClock_;
    std::vector<std::unique_ptr<Track>> tracks_;
};


#pragma once
#include "track.h"
#include "core/mixer.h"
#include "audio/audio_output.h"
#include "core/event_bus.h"

class Host
{
public:
    Host() : eventBus_(std::make_unique<EventBus>());
    EventBus &GetEventBus() { return *eventBus_; }

    Track &CreateTrack(std::unique_ptr<Player> player);
    void RemoveTrack(int index);

    void PlayAll();
    void StopAll();

private:
    std::unique_ptr<EventBus> eventBus_;
    std::vector<std::unique_ptr<Track>> tracks_;
    std::unique_ptr<AudioOutput> audioOutput_;
    std::unique_ptr<AudioClock> audioClock_;
    Mixer mixer_;
};

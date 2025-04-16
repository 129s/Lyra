
#pragma once
#include "audio/audio_output.h"
#include "core/track.h"
#include "core/mixer.h"
#include "core/audio_clock.h"
#include "core/event_bus.h"
#include "core/controller.h"

class Host
{
public:
    Host() : eventBus_(std::make_unique<EventBus>()),
             mixer_(),
             audioOutput_(std::make_unique<AudioOutput>(mixer_, 44100, 512)),
             audioClock_(std::make_unique<AudioClock>(*audioOutput_)) {}

    EventBus &GetEventBus() { return *eventBus_; }

    void AddTrack(std::unique_ptr<Player> player)
    {
        auto &track = tracks_.emplace_back();
        track.BindPlayer(std::move(player));
        mixer_.AddTrack(&track);
    }

    void RemoveTrack(int index);

private:
    Controller controller_;
    std::unique_ptr<EventBus> eventBus_;
    Mixer mixer_;
    std::unique_ptr<AudioOutput> audioOutput_;
    std::unique_ptr<AudioClock> audioClock_;
    std::vector<Track> tracks_;
};
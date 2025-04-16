
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

    void AddTrack(std::unique_ptr<Player> player)
    {
        auto &track = tracks_.emplace_back();
        track.BindPlayer(std::move(player));
        controller_.ConnectTrackToPlayer(tracks_.size() - 1, track.GetPlayer());
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
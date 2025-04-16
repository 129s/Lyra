
#pragma once
#include "track.h"
#include "core/mixer.h"
#include "audio/audio_output.h"

class Host
{
public:
    Host();

    Track &CreateTrack(std::unique_ptr<Player> player);
    void RemoveTrack(int index);

    void PlayAll();
    void StopAll();

private:
    std::vector<std::unique_ptr<Track>> tracks_;
    std::unique_ptr<AudioOutput> audioOutput_;
    Mixer mixer_;
};
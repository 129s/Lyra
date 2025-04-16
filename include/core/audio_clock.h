
#pragma once

class AudioClock
{
public:
    AudioClock(const AudioOutput &audioOutput)
        : audioOutput_(audioOutput) {}

    double GetTime() const
    {
        return audioOutput_.GetSamplesRendered() /
               static_cast<double>(audioOutput_.GetSampleRate());
    }

private:
    const AudioOutput &audioOutput_;
};
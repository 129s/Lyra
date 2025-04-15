
#pragma once
#include "processor.h"
#include <atomic>
typedef unsigned char byte;

class SineWaveProcessor : public AudioProcessor
{
public:
    SineWaveProcessor(int sampleRate = 44100, int blockSize = 512);

    bool ProcessAudio(float *left, float *right, int numSamples) override;
    void ProcessMidiEvent(const VstMidiEvent &event) override;
    int GetSampleRate() const override { return sampleRate_; }
    int GetBlockSize() const override { return blockSize_; }

private:
    const int sampleRate_;
    const int blockSize_;
    double phase_{0.0};
    double frequency_{0.0};
    double amplitude_{0.0};
};
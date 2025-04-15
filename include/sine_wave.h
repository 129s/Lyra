
#pragma once
#include "processor.h"
#include <atomic>
typedef unsigned char byte;

class SineWaveProcessor : public AudioProcessor
{
public:
    SineWaveProcessor(int sampleRate = 441000, int blockSize = 512);

    bool ProcessAudio(float *left, float *right, int numSamples) override;
    void ProcessMidiEvent(const VstMidiEvent &event) override;
    int GetSampleRate() const override { return sampleRate_; }
    int GetBlockSize() const override { return blockSize_; }

    void SetEnvelope(float attack_ms, float release_ms)
    {
        attack_samples_ = static_cast<int>(attack_ms * sampleRate_ / 1000);
        release_samples_ = static_cast<int>(release_ms * sampleRate_ / 1000);
    }

private:
    const int sampleRate_;
    const int blockSize_;
    double phase_{0.0};
    double frequency_{0.0};
    double amplitude_{0.0};
    double max_amplitude_{1.0};

    // 包络相关
    enum EnvelopeStage
    {
        kIdle,
        kAttack,
        kRelease
    };
    std::atomic<EnvelopeStage> envelope_stage_{kIdle};
    int attack_samples_ = 0;
    int release_samples_ = 0;
    double envelope_pos_ = 0.0;
};
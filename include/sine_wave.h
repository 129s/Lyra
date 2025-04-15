
#pragma once
#include "processor.h"
#include <atomic>
typedef unsigned char byte;

enum EnvelopeStage
{
    kIdle,
    kAttack,
    kRelease
};

struct SineVoice
{
    double phase = 0.0;             // 独立相位
    double frequency = 0.0;         // 当前频率
    double amplitude = 0.0;         // 当前振幅
    double release_start_amp = 0.0; // Release起始振幅
    EnvelopeStage stage = kIdle;    // 包络状态
    int envelope_pos = 0;           // 包络位置计数器
    int note = -1;                  // 关联的MIDI音符编号（-1表示未使用）
};

class SineWaveProcessor : public AudioProcessor
{
public:
    SineWaveProcessor(int sampleRate = 441000, int blockSize = 512);

    bool ProcessAudio(float *left, float *right, int numSamples) override;
    void ProcessMidiEvent(const VstMidiEvent &event) override;
    void ActivateVoice(int idx, int note, int velocity);
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
    const int max_voices_ = 8;      // 最大复音数
    std::vector<SineVoice> voices_; // 音轨池
    std::mutex voice_mutex_;        // 线程安全锁

    // 包络参数
    std::atomic<EnvelopeStage> envelope_stage_{kIdle};
    int attack_samples_ = 0;
    int release_samples_ = 0;
    double envelope_pos_ = 0.0;
};
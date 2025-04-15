#include <iostream>

#include "sine_wave.h"
#include <cmath>
#define M_PI 3.14159265358979323846

SineWaveProcessor::SineWaveProcessor(int sampleRate, int blockSize)
    : sampleRate_(sampleRate), blockSize_(blockSize)
{
    voices_.resize(max_voices_); // 分配音轨
}

void SineWaveProcessor::ProcessMidiEvent(const VstMidiEvent &event)
{
    const byte status = event.midiData[0] & 0xF0;
    const byte note = event.midiData[1];
    const byte velocity = event.midiData[2];

    std::lock_guard<std::mutex> lock(voice_mutex_);

    if (status == 0x90 && velocity > 0)
    { // Note On
        // 查找空闲音轨或最旧的Release音轨
        auto oldest_release = -1;
        int oldest_age = -1;
        for (int i = 0; i < max_voices_; ++i)
        {
            if (voices_[i].note == -1)
            {
                // 找到空闲音轨
                ActivateVoice(i, note, velocity);
                return;
            }
            if (voices_[i].stage == kRelease)
            {
                const int age = voices_[i].envelope_pos;
                if (age > oldest_age)
                {
                    oldest_age = age;
                    oldest_release = i;
                }
            }
        }

        // 没有空闲音轨则抢占最旧的Release音轨
        if (oldest_release != -1)
        {
            ActivateVoice(oldest_release, note, velocity);
        }
    }
    else if (status == 0x80 || (status == 0x90 && velocity == 0))
    { // Note Off
        // 查找对应音符的音轨
        for (auto &voice : voices_)
        {
            if (voice.note == note && voice.stage != kRelease)
            {
                voice.stage = kRelease;
                voice.release_start_amp = voice.amplitude;
                voice.envelope_pos = 0;
            }
        }
    }
}

// 新增：激活音轨
void SineWaveProcessor::ActivateVoice(int idx, int note, int velocity)
{
    auto &voice = voices_[idx];
    voice.note = note;
    voice.frequency = 440.0 * pow(2.0, (note - 69) / 12.0);
    voice.phase = 0.0;
    voice.amplitude = 0.0;
    voice.stage = kAttack;
    voice.envelope_pos = 0;
    voice.max_amplitude = velocity / 127.0f;
}

bool SineWaveProcessor::ProcessAudio(float *left, float *right, int numSamples)
{
    // 清零输出缓冲区
    memset(left, 0, numSamples * sizeof(float));
    memset(right, 0, numSamples * sizeof(float));

    const double phase_inc = 2.0 * M_PI / sampleRate_;

    std::lock_guard<std::mutex> lock(voice_mutex_);

    for (auto &voice : voices_)
    {
        if (voice.note == -1)
            continue; // 跳过未使用音轨

        double *freq_ptr = &voice.frequency;
        double *phase_ptr = &voice.phase;
        double *amp_ptr = &voice.amplitude;

        for (int i = 0; i < numSamples; ++i)
        {
            // 处理包络
            switch (voice.stage)
            {
            case kAttack:
            {
                const double progress = static_cast<double>(voice.envelope_pos) / attack_samples_;
                *amp_ptr = progress;
                if (++voice.envelope_pos >= attack_samples_)
                {
                    voice.stage = kIdle;
                }
                break;
            }
            case kRelease:
            {
                const double progress = static_cast<double>(voice.envelope_pos) / release_samples_;
                *amp_ptr = voice.release_start_amp * (voice.max_amplitude - progress);
                if (++voice.envelope_pos >= release_samples_)
                {
                    voice.stage = kIdle;
                    *amp_ptr = 0.0;
                    voice.note = -1; // 标记音轨为空闲
                }
                break;
            }
            case kIdle:
                break;
            }

            // 生成波形
            const double sample = *amp_ptr * voice.max_amplitude * sin(*phase_ptr);
            left[i] += sample;
            right[i] += sample;

            // 更新相位
            *phase_ptr += *freq_ptr * phase_inc;
            if (*phase_ptr >= 2.0 * M_PI)
            {
                *phase_ptr -= 2.0 * M_PI;
            }
        }

        // 削波防止爆音
        for (int i = 0; i < numSamples; ++i)
        {
            left[i] = std::max(-1.0f, std::min(left[i], 1.0f));
            right[i] = std::max(-1.0f, std::min(right[i], 1.0f));
        }
    }

    return true;
}

#pragma once
#include "core/mixer.h"
#include <Windows.h>
#include <mmsystem.h>
#include <thread>
#include <queue>
#include <atomic>
#include <mutex>

class AudioOutput
{
public:
    double GetCurrentTime() const { return samplesRendered_ / static_cast<double>(sampleRate_); } // 全局时间戳（秒）

    AudioOutput(Mixer &mixer, int sampleRate, int bufferSize)
        : mixer_(mixer), sampleRate_(sampleRate), bufferSize_(bufferSize) {}
    ~AudioOutput();

    void Start();
    void Stop();

private:
    void ProcessingLoop();
    static void CALLBACK WaveOutCallback(HWAVEOUT hwo, UINT uMsg, DWORD_PTR instance, DWORD_PTR param1, DWORD_PTR param2);

    Mixer &mixer_;
    HWAVEOUT waveOut_;
    std::thread processingThread_;
    std::atomic<bool> running_{false};
    std::atomic<uint64_t> samplesRendered_{0}; // 累计已渲染的采样数
    std::queue<WAVEHDR *> freeBuffers_;
    std::mutex bufferMutex_;
    const int sampleRate_;
    const int bufferSize_;
};
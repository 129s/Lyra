
#pragma once
#include <Windows.h>
#include <mmsystem.h>
#include <thread>
#include <atomic>
#include "host.h"

class AudioOutput
{
public:
    AudioOutput(VSTHost &host);
    ~AudioOutput();

    bool Initialize();
    void Start();
    void Stop();

private:
    void ProcessingLoop();
    static void CALLBACK WaveOutCallback(HWAVEOUT hwo, UINT uMsg, DWORD_PTR instance, DWORD_PTR param1, DWORD_PTR param2);

    VSTHost &host_;
    HWAVEOUT waveOut_;
    WAVEHDR buffers_[8];
    std::queue<WAVEHDR *> availableBuffers_;
    std::mutex bufferMutex_;
    std::thread processingThread_;
    std::atomic<bool> running_{false};
};
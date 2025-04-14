#include "audio.h"
#include <iostream>

AudioOutput::AudioOutput(VSTHost &host)
    : host_(host), waveOut_(nullptr) {}

AudioOutput::~AudioOutput()
{
    Stop();
    if (waveOut_)
    {
        waveOutReset(waveOut_);
        for (auto &buf : buffers_)
        {
            waveOutUnprepareHeader(waveOut_, &buf, sizeof(WAVEHDR));
            delete[] buf.lpData;
        }
        waveOutClose(waveOut_);
    }
}

bool AudioOutput::Initialize()
{
    WAVEFORMATEX waveFormat{};
    waveFormat.wFormatTag = WAVE_FORMAT_PCM;
    waveFormat.nChannels = 2;
    waveFormat.nSamplesPerSec = host_.GetSampleRate();
    waveFormat.wBitsPerSample = 16;
    waveFormat.nBlockAlign = (waveFormat.nChannels * waveFormat.wBitsPerSample) / 8;
    waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;

    if (waveOutOpen(&waveOut_, WAVE_MAPPER, &waveFormat,
                    (DWORD_PTR)WaveOutCallback, (DWORD_PTR)this, CALLBACK_FUNCTION) != MMSYSERR_NOERROR)
    {
        std::cerr << "无法打开音频设备" << std::endl;
        return false;
    }

    const int bufferSize = host_.GetBlockSize() * waveFormat.nBlockAlign;
    for (auto &buf : buffers_)
    {
        buf.lpData = new char[bufferSize];
        buf.dwBufferLength = bufferSize;
        waveOutPrepareHeader(waveOut_, &buf, sizeof(WAVEHDR));
        availableBuffers_.push(&buf);
    }

    return true;
}

void AudioOutput::Start()
{
    running_ = true;
    processingThread_ = std::thread(&AudioOutput::ProcessingLoop, this);
}

void AudioOutput::Stop()
{
    running_ = false;
    if (processingThread_.joinable())
        processingThread_.join();
}

void CALLBACK AudioOutput::WaveOutCallback(HWAVEOUT hwo, UINT uMsg,
                                           DWORD_PTR instance, DWORD_PTR param1, DWORD_PTR param2)
{
    auto *self = reinterpret_cast<AudioOutput *>(instance);
    if (uMsg == WOM_DONE)
    {
        auto *hdr = reinterpret_cast<WAVEHDR *>(param1);
        std::lock_guard<std::mutex> lock(self->bufferMutex_);
        self->availableBuffers_.push(hdr);
    }
}

void AudioOutput::ProcessingLoop()
{
    const int blockSize = host_.GetBlockSize();
    float *outputs[] = {new float[blockSize], new float[blockSize]};

    while (running_)
    {
        WAVEHDR *hdr = nullptr;
        {
            std::unique_lock<std::mutex> lock(bufferMutex_);
            if (availableBuffers_.empty())
                continue;
            hdr = availableBuffers_.front();
            availableBuffers_.pop();
        }

        host_.ProcessMidiEvents();
        host_.ProcessAudio(nullptr, outputs, blockSize);

        // 转换为16-bit PCM
        auto *pcm = reinterpret_cast<short *>(hdr->lpData);
        for (int i = 0; i < blockSize; ++i)
        {
            pcm[i * 2] = static_cast<short>(outputs[0][i] * 32767.0f);
            pcm[i * 2 + 1] = static_cast<short>(outputs[1][i] * 32767.0f);
        }

        waveOutWrite(waveOut_, hdr, sizeof(WAVEHDR));
    }

    delete[] outputs[0];
    delete[] outputs[1];
}
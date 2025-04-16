
#include "audio/audio_output.h"
#include <stdexcept>

AudioOutput::~AudioOutput()
{
    Stop();
    if (waveOut_ != nullptr)
    {
        waveOutReset(waveOut_);
        for (WAVEHDR *hdr; !freeBuffers_.empty(); freeBuffers_.pop())
        {
            hdr = freeBuffers_.front();
            waveOutUnprepareHeader(waveOut_, hdr, sizeof(WAVEHDR));
            delete[] hdr->lpData;
            delete hdr;
        }
        waveOutClose(waveOut_);
    }
}

void AudioOutput::Start()
{
    WAVEFORMATEX format;
    format.wFormatTag = WAVE_FORMAT_IEEE_FLOAT;
    format.nChannels = 2;
    format.nSamplesPerSec = sampleRate_;
    format.wBitsPerSample = 32;
    format.nBlockAlign = (format.nChannels * format.wBitsPerSample) / 8;
    format.nAvgBytesPerSec = format.nSamplesPerSec * format.nBlockAlign;
    format.cbSize = 0;

    MMRESULT result = waveOutOpen(&waveOut_, WAVE_MAPPER, &format,
                                  reinterpret_cast<DWORD_PTR>(&AudioOutput::WaveOutCallback),
                                  reinterpret_cast<DWORD_PTR>(this), CALLBACK_FUNCTION);

    if (result != MMSYSERR_NOERROR)
    {
        throw std::runtime_error("Failed to open audio device");
    }

    // 预分配缓冲区
    for (int i = 0; i < 4; ++i)
    {
        WAVEHDR *hdr = new WAVEHDR;
        hdr->lpData = new char[bufferSize_ * sizeof(float) * 2]; // stereo
        hdr->dwBufferLength = bufferSize_ * sizeof(float) * 2;
        hdr->dwFlags = 0;
        waveOutPrepareHeader(waveOut_, hdr, sizeof(WAVEHDR));
        freeBuffers_.push(hdr);
    }

    running_ = true;
    processingThread_ = std::thread(&AudioOutput::ProcessingLoop, this);
}

void AudioOutput::Stop()
{
    running_ = false;
    if (processingThread_.joinable())
    {
        processingThread_.join();
    }
}

void AudioOutput::ProcessingLoop()
{
    while (running_)
    {
        std::unique_lock lock(bufferMutex_);
        if (!freeBuffers_.empty())
        {
            WAVEHDR *hdr = freeBuffers_.front();
            freeBuffers_.pop();
            lock.unlock();

            // 从混音器获取音频数据
            float *buffer = reinterpret_cast<float *>(hdr->lpData);
            mixer_.Mix(buffer, buffer + bufferSize_, bufferSize_);

            waveOutWrite(waveOut_, hdr, sizeof(WAVEHDR));
            samplesRendered_ += bufferSize_;
        }
    }
}

void CALLBACK AudioOutput::WaveOutCallback(HWAVEOUT, UINT uMsg,
                                           DWORD_PTR instance, DWORD_PTR param1, DWORD_PTR)
{
    AudioOutput *self = reinterpret_cast<AudioOutput *>(instance);
    if (uMsg == WOM_DONE)
    {
        WAVEHDR *hdr = reinterpret_cast<WAVEHDR *>(param1);
        std::lock_guard lock(self->bufferMutex_);
        self->freeBuffers_.push(hdr);
    }
}
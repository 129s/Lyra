#include "audio.h"
#include <iostream>

AudioOutput::AudioOutput(VSTHost &host)
    : host_(host), waveOut_(nullptr) {}

AudioOutput::~AudioOutput()
{
    Stop(); // 停止音频处理线程

    // 释放音频资源
    if (waveOut_)
    {
        waveOutReset(waveOut_); // 重置音频设备，停止播放

        // 释放缓冲区资源
        for (auto &buf : buffers_)
        {
            waveOutUnprepareHeader(waveOut_, &buf, sizeof(WAVEHDR)); // 取消准备波形头
            delete[] buf.lpData;                                     // 释放缓冲区内存
        }

        waveOutClose(waveOut_); // 关闭音频设备
    }
}

bool AudioOutput::Initialize()
{
    // 定义音频格式
    WAVEFORMATEX waveFormat{};
    waveFormat.wFormatTag = WAVE_FORMAT_PCM;                                         // PCM格式
    waveFormat.nChannels = 2;                                                        // 立体声
    waveFormat.nSamplesPerSec = host_.GetSampleRate();                               // 采样率从VSTHost获取
    waveFormat.wBitsPerSample = 16;                                                  // 16位采样
    waveFormat.nBlockAlign = (waveFormat.nChannels * waveFormat.wBitsPerSample) / 8; // 块对齐
    waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign; // 平均字节速率

    // 打开音频设备
    if (waveOutOpen(&waveOut_, WAVE_MAPPER, &waveFormat,
                    (DWORD_PTR)WaveOutCallback, (DWORD_PTR)this, CALLBACK_FUNCTION) != MMSYSERR_NOERROR)
    {
        std::cerr << "无法打开音频设备" << std::endl;
        return false;
    }

    // 分配和准备音频缓冲区
    const int bufferSize = host_.GetBlockSize() * waveFormat.nBlockAlign; // 缓冲区大小 = 块大小 * 块对齐
    for (auto &buf : buffers_)
    {
        buf.lpData = new char[bufferSize];                     // 分配缓冲区内存
        buf.dwBufferLength = bufferSize;                       // 设置缓冲区长度
        waveOutPrepareHeader(waveOut_, &buf, sizeof(WAVEHDR)); // 准备波形头
        availableBuffers_.push(&buf);                          // 将缓冲区添加到可用缓冲区队列
    }

    return true;
}

void AudioOutput::Start()
{
    running_ = true;                                                     // 设置运行标志
    processingThread_ = std::thread(&AudioOutput::ProcessingLoop, this); // 启动音频处理线程
}

void AudioOutput::Stop()
{
    running_ = false; // 设置运行标志为false，停止处理循环
    if (processingThread_.joinable())
        processingThread_.join(); // 等待音频处理线程结束
}

// 音频输出回调函数
void CALLBACK AudioOutput::WaveOutCallback(HWAVEOUT hwo, UINT uMsg,
                                           DWORD_PTR instance, DWORD_PTR param1, DWORD_PTR param2)
{
    auto *self = reinterpret_cast<AudioOutput *>(instance); // 获取AudioOutput实例指针

    // 当缓冲区播放完成时
    if (uMsg == WOM_DONE)
    {
        auto *hdr = reinterpret_cast<WAVEHDR *>(param1); // 获取已完成的波形头

        // 将缓冲区返回到可用缓冲区队列
        std::lock_guard<std::mutex> lock(self->bufferMutex_); // 加锁，保证线程安全
        self->availableBuffers_.push(hdr);                    // 将缓冲区添加到可用缓冲区队列
    }
}

// 音频处理循环
void AudioOutput::ProcessingLoop()
{
    const int blockSize = host_.GetBlockSize();                      // 获取块大小
    float *outputs[] = {new float[blockSize], new float[blockSize]}; // 创建输出缓冲区（左右声道）

    // 循环处理音频
    while (running_)
    {
        WAVEHDR *hdr = nullptr;

        // 从可用缓冲区队列中获取一个缓冲区
        {
            std::unique_lock<std::mutex> lock(bufferMutex_); // 使用unique_lock，允许条件变量
            if (availableBuffers_.empty())
                continue;                    // 如果没有可用缓冲区，则继续循环
            hdr = availableBuffers_.front(); // 获取队列头部的缓冲区
            availableBuffers_.pop();         // 从队列中移除缓冲区
        }

        host_.ProcessMidiEvents();                       // 处理MIDI事件
        host_.ProcessAudio(nullptr, outputs, blockSize); // 处理音频，将结果写入输出缓冲区

        // 将浮点音频数据转换为16-bit PCM格式
        auto *pcm = reinterpret_cast<short *>(hdr->lpData); // 获取缓冲区指针
        for (int i = 0; i < blockSize; ++i)
        {
            pcm[i * 2] = static_cast<short>(outputs[0][i] * 32767.0f);     // 左声道
            pcm[i * 2 + 1] = static_cast<short>(outputs[1][i] * 32767.0f); // 右声道
        }

        waveOutWrite(waveOut_, hdr, sizeof(WAVEHDR)); // 将缓冲区写入音频设备进行播放
    }

    delete[] outputs[0]; // 释放输出缓冲区内存
    delete[] outputs[1]; // 释放输出缓冲区内存
}

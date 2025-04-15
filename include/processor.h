
#pragma once
#include <vector>
#include "midi.h"

class AudioProcessor
{
public:
    virtual ~AudioProcessor() = default;

    // 处理音频生成，返回是否激活状态
    virtual bool ProcessAudio(float *left, float *right, int numSamples) = 0;

    // 处理MIDI事件
    virtual void ProcessMidiEvent(const VstMidiEvent &event) = 0;

    // 获取当前采样率
    virtual int GetSampleRate() const = 0;

    // 获取音频块大小
    virtual int GetBlockSize() const = 0;
};
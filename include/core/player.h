
#pragma once
#include "event.h"
#include <vector>

class Player
{
public:
    virtual ~Player() = default;

    // 处理MIDI事件流
    virtual void ProcessMidiEvents(const std::vector<MidiEvent> &events) = 0;

    // 生成音频块（返回是否还有音频输出）
    virtual bool RenderAudio(float *left, float *right, int numSamples) = 0;

    // 重置状态（如停止时）
    virtual void Reset() = 0;
};

#include "core/mixer.h"
#include "core/track.h"

void Mixer::Mix(float *left, float *right, int numSamples)
{
    // 清空输出缓冲区
    memset(left, 0, numSamples * sizeof(float));
    memset(right, 0, numSamples * sizeof(float));

    // 临时缓冲区初始化
    tempLeft_.resize(numSamples);
    tempRight_.resize(numSamples);

    // 累加所有轨道的音频输出
    for (auto track : tracks_)
    {
        // 清空临时缓冲区
        memset(tempLeft_.data(), 0, numSamples * sizeof(float));
        memset(tempRight_.data(), 0, numSamples * sizeof(float));

        // 渲染轨道音频到临时缓冲区
        track->RenderAudio(tempLeft_.data(), tempRight_.data(), numSamples);

        // 混合到主缓冲区（简单叠加）
        for (int i = 0; i < numSamples; ++i)
        {
            left[i] += tempLeft_[i];
            right[i] += tempRight_[i];
        }
    }
}
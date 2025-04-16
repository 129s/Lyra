
#pragma once
#include <vector>

class Mixer
{
public:
    // 混合多个轨道的音频到同一缓冲区
    void Mix(float *left, float *right, int numSamples);

    // 添加轨道到混合器
    void AddTrack(class Track *track);
    void RemoveTrack(class Track *track);

private:
    std::vector<class Track *> tracks_;
    std::vector<float> tempLeft_;  // 临时左声道缓冲区
    std::vector<float> tempRight_; // 临时右声道缓冲区
};
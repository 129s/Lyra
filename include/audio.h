#pragma once
#include <windows.h>
#include "mixer.h"

// 双声道配置
#define NUM_CHANNELS 2
// 音频参数配置
#define SAMPLE_RATE 44100
#define BUFFER_SIZE 4096 // 缓冲区大小（样本数）
#define NUM_BUFFERS 2    // 双缓冲

typedef struct
{
    HWAVEOUT hWaveOut;
    WAVEHDR buffers[NUM_BUFFERS];
    Mixer *mixer;       // 混音器指针
    double sample_rate; // 采样率
} AudioContext;

// 初始化音频设备
int audio_init(AudioContext *ctx, int sample_rate);
// 开始播放
void audio_play(AudioContext *ctx);
// 停止并释放资源
void audio_cleanup(AudioContext *ctx);
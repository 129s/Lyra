#pragma once
#include <windows.h>
#include "mixer.h"

// 双声道配置
#define NUM_CHANNELS 2
// 音频参数配置
#define SAMPLE_RATE 44100
#define BUFFER_SIZE 512 // 缓冲区大小（样本数）
#define NUM_BUFFERS 8

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
// 关闭音频
void audio_close(AudioContext *ctx);
#pragma once
#include <stdbool.h>

typedef enum
{
    WAVE_SINE,
    WAVE_SQUARE,
    WAVE_SAWTOOTH,
    WAVE_TRIANGLE
} WaveType;

typedef struct
{
    float frequency;    // 基频（Hz）
    int amplitude;      // 振幅（0-32767）
    WaveType wave_type; // 波形类型
    double phase;       // 当前相位（替代全局time
    bool active;        // 是否激活
} WaveGenerator;

// 初始化生成器
void wave_init(WaveGenerator *gen, WaveType type, float freq, int amp);
// 生成下一个样本
short wave_next(WaveGenerator *gen, double sample_rate);
// 开关
void wave_trigger(WaveGenerator *gen, bool on);
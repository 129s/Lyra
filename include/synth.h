#pragma once
#include <stdbool.h>
#include <stdint.h>

typedef enum
{
    WAVE_SINE,
    WAVE_SQUARE,
    WAVE_SAWTOOTH,
    WAVE_TRIANGLE
} WaveType;

#define MAX_VOICES 8

typedef struct
{
    bool active;
    float frequency;
    int amplitude;
    WaveType wave_type;
    double phase;
    uint8_t note;
} Voice;

typedef struct
{
    Voice voices[MAX_VOICES];
    WaveType default_wave;
    int default_amp;
    float master_vol;
} Synth;

// MIDI处理接口
void synth_init(Synth *synth);
void synth_midi_in(Synth *synth, const uint8_t *msg);

// 音频处理接口
short synth_process(Synth *synth, double sample_rate);
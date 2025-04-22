
#pragma once
#include <windows.h>
#include <stdint.h>

typedef void (*MidiCallback)(uint8_t status, uint8_t data1, uint8_t data2, void *user);

// MIDI输入设备初始化
int midi_init(MidiCallback callback, void *user);
void midi_close();
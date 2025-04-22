#pragma once
#include <windows.h>
#include "synth.h"

typedef struct
{
    HWND hWnd;
    HDC hdcBuffer;
    HBITMAP hbmBuffer;
    RECT clientRect;
    int octave;
    WaveType waveType;
} GUI;

// 初始化GUI
GUI *gui_create(HINSTANCE hInstance);
// 处理窗口消息
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
// 更新显示
void gui_update(GUI *gui, const Synth *synth);
// 销毁资源
void gui_destroy(GUI *gui);
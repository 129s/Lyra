#pragma once
#include <windows.h>
#include "synth.h"

// 修改GUI结构体
typedef struct
{
    HWND hWnd;
    HDC hdcBuffer;
    HBITMAP hbmBuffer;
    RECT clientRect;
    Synth *synth;       // 关联合成器指针
    int wave_sel_index; // 当前选择的波形索引
} GUI;

// 初始化GUI
GUI *gui_create(HINSTANCE hInstance, Synth *synth);
// 处理窗口消息
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
// 更新显示
void gui_update(GUI *gui, const Synth *synth);
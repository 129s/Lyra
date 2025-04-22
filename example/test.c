
#include <stdio.h>
#include <windows.h>
#include "audio.h"
#include "synth.h"
#include "keyboard.h"
#include "gui.h"

static void midi_handler(uint8_t status, uint8_t data1, uint8_t data2, void *user)
{
    Synth *synth = (Synth *)user;
    uint8_t msg[] = {status, data1, data2};
    synth_midi_in(synth, msg);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // 初始化音频上下文
    AudioContext ctx = {0};
    if (audio_init(&ctx, SAMPLE_RATE) != MMSYSERR_NOERROR)
    {
        MessageBox(NULL, "Audio initialization failed!", "Error", MB_ICONERROR);
        return 1;
    }

    // 初始化合成器
    Synth synth;
    synth_init(&synth);
    mixer_add(ctx.mixer, &synth);

    // 初始化键盘和GUI
    keyboard_init(midi_handler, &synth);
    GUI *gui = gui_create(hInstance); // 使用WinMain的hInstance
    synth.default_wave = WAVE_SQUARE;

    // 开始播放音频
    audio_play(&ctx);

    // 主消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        // 处理对话框消息
        if (IsWindow(gui->hWnd) && IsDialogMessage(gui->hWnd, &msg))
            continue;

        // 处理键盘退出
        if (msg.message == WM_KEYDOWN && msg.wParam == VK_ESCAPE)
            DestroyWindow(gui->hWnd);

        TranslateMessage(&msg);
        DispatchMessage(&msg);

        // 更新GUI显示
        gui_update(gui, &synth);
    }

    // 清理资源
    keyboard_close();
    audio_cleanup(&ctx);
    gui_destroy(gui);
    return 0;
}
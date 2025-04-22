
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

    // 初始化键盘
    keyboard_init(midi_handler, &synth);

    // 初始化GUI
    GUI *gui = gui_create(hInstance, &synth);

    // 开始播放音频
    audio_play(&ctx);

    // 主消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
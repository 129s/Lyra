// === 修改文件：example/test.c ===
#include <stdio.h>
#include <windows.h>
#include <process.h> // 添加线程支持
#include "audio.h"
#include "synth.h"
#include "keyboard.h"
#include "gui.h"

// 添加线程同步对象
static HANDLE hAudioThread = NULL;
static CRITICAL_SECTION audioCS;

static void midi_handler(uint8_t status, uint8_t data1, uint8_t data2, void *user)
{
    Synth *synth = (Synth *)user;
    uint8_t msg[] = {status, data1, data2};
    synth_midi_in(synth, msg);
}

// 音频线程函数
static DWORD WINAPI audio_thread(LPVOID lpParam)
{
    AudioContext *ctx = (AudioContext *)lpParam;

    EnterCriticalSection(&audioCS);
    audio_play(ctx);
    LeaveCriticalSection(&audioCS);

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // 初始化临界区
    InitializeCriticalSection(&audioCS);

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

    // 创建音频线程
    hAudioThread = CreateThread(
        NULL,         // 默认安全属性
        0,            // 默认栈大小
        audio_thread, // 线程函数
        &ctx,         // 参数
        0,            // 默认创建标志
        NULL);        // 不需要线程ID

    if (hAudioThread == NULL)
    {
        MessageBox(NULL, "Failed to create audio thread!", "Error", MB_ICONERROR);
        return 1;
    }

    // 主消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
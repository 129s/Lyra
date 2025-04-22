// example/test.c
#include <stdio.h>
#include <windows.h>
#include "audio.h"
#include "synth.h"
#include "keyboard.h"

static void midi_handler(uint8_t status, uint8_t data1, uint8_t data2, void *user)
{
    Synth *synth = (Synth *)user;
    uint8_t msg[] = {status, data1, data2};
    synth_midi_in(synth, msg);
}

int main()
{
    AudioContext ctx = {0};
    if (audio_init(&ctx, SAMPLE_RATE) != MMSYSERR_NOERROR)
    {
        fprintf(stderr, "Audio init failed!\n");
        return 1;
    }

    Synth synth;
    synth_init(&synth);
    synth.default_wave = WAVE_SAWTOOTH;
    mixer_add(ctx.mixer, &synth);

    keyboard_init(midi_handler, &synth);
    audio_play(&ctx);

    printf("Playing...\n");

    // 消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (msg.message == WM_KEYDOWN && msg.wParam == VK_ESCAPE)
            break;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    keyboard_close();
    audio_cleanup(&ctx);
    return 0;
}
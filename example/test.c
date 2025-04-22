
#include <stdio.h>
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
    synth.default_wave = WAVE_SQUARE;
    mixer_add(ctx.mixer, &synth);

    // 初始化键盘输入
    keyboard_init(midi_handler, &synth);

    audio_play(&ctx);
    printf("Playing... Use keyboard (A-J,W,E,T,Y,U) to play notes. Press Enter to exit.\n");
    getchar();

    keyboard_close();
    audio_cleanup(&ctx);
    return 0;
}
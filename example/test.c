#include <stdio.h>
#include "audio.h"

int main()
{
    AudioContext ctx = {0}; // 注意生命周期
    if (audio_init(&ctx, SAMPLE_RATE) != MMSYSERR_NOERROR)
    {
        fprintf(stderr, "Failed to open audio device!\n");
        return 1;
    }

    // 创建两个生成器并添加到混音器
    WaveGenerator gen1, gen2, gen3;
    wave_init(&gen1, WAVE_SINE, 880.0f, 30000);
    wave_init(&gen2, WAVE_SQUARE, 220.0f, 15000);
    wave_init(&gen3, WAVE_SAWTOOTH, 440.0f, 30000);
    mixer_add(ctx.mixer, &gen1);
    mixer_add(ctx.mixer, &gen2);
    mixer_add(ctx.mixer, &gen3);

    audio_play(&ctx);

    printf("Playing... Press Enter to stop.\n");
    getchar();
    audio_cleanup(&ctx);
    return 0;
}
#include <stdio.h>
#include "audio.h"
#include "synth.h"

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

    // 演奏C大调和弦
    uint8_t chord[] = {60, 64, 67}; // C4, E4, G4
    for (int i = 0; i < 3; i++)
    {
        uint8_t msg[] = {0x90, chord[i], 0x7F};
        synth_midi_in(&synth, msg);
    }

    audio_play(&ctx);
    printf("Playing chord... Press Enter to stop.\n");
    getchar();

    audio_cleanup(&ctx);
    return 0;
}
#include <stdio.h>
#include "audio.h"
#include "synth.h"

static void CALLBACK waveOutProc(HWAVEOUT, UINT, DWORD_PTR, DWORD_PTR, DWORD_PTR);
static void fill_buffer(WAVEHDR *header, AudioContext *ctx);

int audio_init(AudioContext *ctx, int sample_rate)
{
    WAVEFORMATEX format = {
        .wFormatTag = WAVE_FORMAT_PCM,
        .nChannels = NUM_CHANNELS, // 双声道
        .nSamplesPerSec = sample_rate,
        .wBitsPerSample = 16,
        .nBlockAlign = NUM_CHANNELS * sizeof(short),
        .nAvgBytesPerSec = sample_rate * NUM_CHANNELS * sizeof(short),
    };

    ctx->mixer = mixer_create();
    ctx->sample_rate = sample_rate;

    return waveOutOpen(&ctx->hWaveOut, WAVE_MAPPER, &format, (DWORD_PTR)waveOutProc, (DWORD_PTR)ctx, CALLBACK_FUNCTION);
}

void audio_play(AudioContext *ctx)
{
    for (int i = 0; i < NUM_BUFFERS; ++i)
    {
        ctx->buffers[i].lpData = (LPSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, BUFFER_SIZE * NUM_CHANNELS * sizeof(short));
        ctx->buffers[i].dwBufferLength = BUFFER_SIZE * NUM_CHANNELS * sizeof(short);
        waveOutPrepareHeader(ctx->hWaveOut, &ctx->buffers[i], sizeof(WAVEHDR));
        fill_buffer(&ctx->buffers[i], ctx);
        MMRESULT writeResult = waveOutWrite(ctx->hWaveOut, &ctx->buffers[i], sizeof(WAVEHDR));
        if (writeResult != MMSYSERR_NOERROR)
        {
            char errorText[MAXERRORLENGTH];
            waveOutGetErrorText(writeResult, errorText, MAXERRORLENGTH);

            char errorMsg[128];
            sprintf(errorMsg, "Audio error: %s", errorText);
            MessageBox(NULL, errorMsg, "Audio Error", MB_ICONERROR);
            return;
        }
        else
        {
            char debugMsg[64];
            sprintf(debugMsg, "[DEBUG] Buffer %d submitted successfully.\n", i);
            OutputDebugString(debugMsg);
        }
    }
}

void audio_cleanup(AudioContext *ctx)
{
    // 停止播放并取消所有未完成的缓冲区
    waveOutReset(ctx->hWaveOut);

    // 释放 Mixer 及其 Synths
    mixer_free(ctx->mixer);
    // 释放缓冲区内存
    for (int i = 0; i < NUM_BUFFERS; ++i)
    {
        waveOutUnprepareHeader(ctx->hWaveOut, &ctx->buffers[i], sizeof(WAVEHDR));
        HeapFree(GetProcessHeap(), 0, ctx->buffers[i].lpData);
    }
    waveOutClose(ctx->hWaveOut);
}

static void fill_buffer(WAVEHDR *header, AudioContext *ctx)
{
    short *samples = (short *)header->lpData;
    for (int i = 0; i < BUFFER_SIZE; ++i)
    {
        short sample = mixer_process(ctx->mixer, ctx->sample_rate);
        samples[i * 2] = sample;     // 左声道
        samples[i * 2 + 1] = sample; // 右声道
    }
}

static void CALLBACK waveOutProc(
    HWAVEOUT hWave, UINT msg,
    DWORD_PTR instance, DWORD_PTR param1, DWORD_PTR param2)
{
    if (msg == WOM_DONE)
    {
        WAVEHDR *header = (WAVEHDR *)param1;
        AudioContext *ctx = (AudioContext *)instance;

        fill_buffer(header, ctx);
        waveOutWrite(hWave, header, sizeof(WAVEHDR));
    }
}

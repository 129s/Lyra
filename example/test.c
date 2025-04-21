
#include <stdio.h>
#include <conio.h> // 新增键盘输入支持
#include <stdbool.h>
#include "audio.h"
#include "mixer.h"
#define _USE_MATH_DEFINES
#include "math.h"

// 键盘音符映射（ASCII到MIDI音符号）
static const int KEY_NOTE_MAP[][2] = {
    {'a', 60}, // C4
    {'w', 61}, // C#4
    {'s', 62}, // D4
    {'e', 63}, // D#4
    {'d', 64}, // E4
    {'f', 65}, // F4
    {'t', 66}, // F#4
    {'g', 67}, // G4
    {'y', 68}, // G#4
    {'h', 69}, // A4
    {'u', 70}, // A#4
    {'j', 71}, // B4
    {'k', 72}, // C5
    {0, 0}     // 结束标记
};

// 当前激活的音符列表
typedef struct
{
    int note;
    WaveGenerator *gen;
} ActiveNote;

static ActiveNote active_notes[16] = {0};
static Mixer *g_mixer;

// MIDI频率转换函数
static float midi_note_to_freq(int note)
{
    return 440.0f * powf(2.0f, (note - 69) / 12.0f);
}

// 查找音符对应的按键
static int find_note_by_key(int key)
{
    for (int i = 0; KEY_NOTE_MAP[i][0]; i++)
    {
        if (KEY_NOTE_MAP[i][0] == key)
            return KEY_NOTE_MAP[i][1];
    }
    return -1;
}

// 处理键盘输入
static void process_input()
{
    while (_kbhit())
    {
        int key = _getch();
        int note = find_note_by_key(tolower(key));
        printf("%d\t", note);
        if (note > 0)
        {
            // 查找空闲插槽
            int slot = -1;
            for (int i = 0; i < 16; i++)
            {
                if (active_notes[i].note == 0)
                {
                    slot = i;
                    break;
                }
            }

            if (slot != -1)
            {
                // Note On
                WaveGenerator *gen = malloc(sizeof(WaveGenerator));
                wave_init(gen, WAVE_SINE, midi_note_to_freq(note), 30000);
                active_notes[slot] = (ActiveNote){note, gen};
                mixer_add(g_mixer, gen);
            }
        }
    }

    // 检测释放的按键（Windows特有实现）
    for (int i = 0; KEY_NOTE_MAP[i][0]; i++)
    {
        if (!(GetAsyncKeyState(KEY_NOTE_MAP[i][0]) & 0x8000))
        {
            for (int j = 0; j < 16; j++)
            {
                if (active_notes[j].note == KEY_NOTE_MAP[i][1])
                {
                    mixer_remove(g_mixer, active_notes[j].gen);
                    free(active_notes[j].gen);
                    active_notes[j].note = 0;
                    break;
                }
            }
        }
    }
}

int main()
{
    AudioContext ctx = {0};
    if (audio_init(&ctx, SAMPLE_RATE) != MMSYSERR_NOERROR)
    {
        fprintf(stderr, "Failed to open audio device!\n");
        return 1;
    }
    g_mixer = ctx.mixer;

    audio_play(&ctx);
    printf("Keyboard controls:\n");
    printf("A-W-S-E-D-F-T-G-Y-H-U-J-K 对应钢琴键盘\n");
    printf("Press Q to quit\n");

    // 主循环
    bool running = true;
    while (running)
    {
        process_input();
        if (_kbhit() && tolower(_getch()) == 'q')
            running = false;
        Sleep(10); // 降低CPU占用
    }

    audio_cleanup(&ctx);
    return 0;
}
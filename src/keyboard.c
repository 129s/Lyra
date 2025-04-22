
#include "keyboard.h"
#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

#define KEYBOARD_MAP_SIZE 12

static volatile bool running = true;
static HANDLE hThread = NULL;
static MidiCallback midi_callback = NULL;
static void *user_data = NULL;

// 键盘映射 (QWERTY布局)
static const struct
{
    int vk;       // 虚拟键码
    uint8_t note; // MIDI音符
} key_map[KEYBOARD_MAP_SIZE] = {
    {'A', 60}, // C4
    {'W', 61}, // C#4
    {'S', 62}, // D4
    {'E', 63}, // D#4
    {'D', 64}, // E4
    {'F', 65}, // F4
    {'T', 66}, // F#4
    {'G', 67}, // G4
    {'Y', 68}, // G#4
    {'H', 69}, // A4
    {'U', 70}, // A#4
    {'J', 71}, // B4
};

static DWORD WINAPI keyboard_thread(LPVOID lpParam)
{
    bool key_states[KEYBOARD_MAP_SIZE] = {0};

    while (running)
    {
        for (int i = 0; i < KEYBOARD_MAP_SIZE; i++)
        {
            SHORT state = GetAsyncKeyState(key_map[i].vk);
            bool pressed = (state & 0x8000) != 0;

            if (pressed != key_states[i])
            {
                uint8_t msg[3] = {
                    pressed ? 0x90 : 0x80, // Note On/Off
                    key_map[i].note,
                    pressed ? 0x7F : 0x00 // 力度
                };

                if (midi_callback)
                {
                    midi_callback(msg[0], msg[1], msg[2], user_data);
                }
                key_states[i] = pressed;
            }
        }
        Sleep(100); // 降低CPU占用
    }
    return 0;
}

void keyboard_init(MidiCallback callback, void *user)
{
    midi_callback = callback;
    user_data = user;
    running = true;
    hThread = CreateThread(NULL, 0, keyboard_thread, NULL, 0, NULL);
}

void keyboard_close()
{
    running = false;
    if (hThread)
    {
        WaitForSingleObject(hThread, 1000);
        CloseHandle(hThread);
        hThread = NULL;
    }
}
// src/keyboard.c
#include "keyboard.h"
#include <windows.h>
#include <stdio.h>

static HHOOK hKeyboardHook = NULL;
static MidiCallback midi_callback = NULL;
static void *user_data = NULL;

// 键盘映射
static const struct
{
    int vk;          // 虚拟键码
    uint8_t note;    // MIDI音符
    const char *key; // 键位标识（仅注释用）
} key_map[] = {
    // 主演奏区（两个八度）
    {'Z', 48, "Z:C3"},
    {'S', 49, "S:C#3"},
    {'X', 50, "X:D3"},
    {'D', 51, "D:D#3"},
    {'C', 52, "C:E3"},
    {'V', 53, "V:F3"},
    {'G', 54, "G:F#3"},
    {'B', 55, "B:G3"},
    {'H', 56, "H:G#3"},
    {'N', 57, "N:A3"},
    {'J', 58, "J:A#3"},
    {'M', 59, "M:B3"},

    {VK_OEM_COMMA, 60, ",:C4"},
    {'L', 61, "L:C#4"},
    {VK_OEM_PERIOD, 62, ".:D4"},
    {VK_OEM_1, 63, ";:D#4"}, // ;键
    {VK_OEM_2, 64, "/:E4"},
    {'Q', 60, "Q:C4"}, // 兼容两种布局
    {'2', 61, "2:C#4"},
    {'W', 62, "W:D4"},
    {'3', 63, "3:D#4"},
    {'E', 64, "E:E4"},
    {'R', 65, "R:F4"},
    {'5', 66, "5:F#4"},
    {'T', 67, "T:G4"},
    {'6', 68, "6:G#4"},
    {'Y', 69, "Y:A4"},
    {'7', 70, "7:A#4"},
    {'U', 71, "U:B4"},
    {'I', 72, "I:C5"},
    {'9', 73, "9:C#5"},
    {'O', 74, "O:D5"},
    {'0', 75, "0:D#5"},
    {'P', 76, "P:E5"},

    // 八度切换控制键
    {VK_F1, 0xFF, "F1:Oct-"}, // 八度下调
    {VK_F2, 0xFE, "F2:Oct+"}, // 八度上调
};

#define KEY_MAP_SIZE (sizeof(key_map) / sizeof(key_map[0]))

// 全局状态
static int8_t octave_offset = 0;         // 当前八度偏移（±2个八度）
static uint8_t sustain_notes[128] = {0}; // 延音状态跟踪

static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        KBDLLHOOKSTRUCT *pKey = (KBDLLHOOKSTRUCT *)lParam;

        for (int i = 0; i < KEY_MAP_SIZE; i++)
        {
            if (pKey->vkCode == key_map[i].vk)
            {
                uint8_t note = key_map[i].note;
                uint8_t status = 0;

                // 处理控制命令
                if (note >= 0xFE)
                {
                    if (wParam == WM_KEYDOWN)
                    {
                        octave_offset += (note == 0xFE) ? 12 : -12;
                        octave_offset = (octave_offset > 24) ? 24 : (octave_offset < -24) ? -24
                                                                                          : octave_offset;
                    }
                    break;
                }

                // 计算实际音符（含八度偏移）
                int actual_note = note + octave_offset;
                if (actual_note < 0 || actual_note > 127)
                    break;

                // 生成MIDI事件
                if (wParam == WM_KEYDOWN)
                {
                    status = 0x90;
                    sustain_notes[actual_note] = 1;
                }
                else
                {
                    status = 0x80;
                    sustain_notes[actual_note] = 0;
                }

                uint8_t msg[] = {status, (uint8_t)actual_note,
                                 (status == 0x90) ? 0x7F : 0x00};

                if (midi_callback)
                {
                    midi_callback(msg[0], msg[1], msg[2], user_data);
                }
                break;
            }
        }
    }
    return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}

void keyboard_init(MidiCallback callback, void *user)
{
    midi_callback = callback;
    user_data = user;

    // 使用WH_KEYBOARD_LL钩子（需设置消息循环）
    hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, GetModuleHandle(NULL), 0);
}

void keyboard_close()
{
    if (hKeyboardHook)
    {
        UnhookWindowsHookEx(hKeyboardHook);
        hKeyboardHook = NULL;
    }
}
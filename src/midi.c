// src/midi.c
#include "midi.h"
#include <stdio.h>

static HMIDIIN hMidiIn = NULL;
static MidiCallback g_callback = NULL;
static void *g_user_data = NULL;

static void CALLBACK MidiInProc(HMIDIIN hMidi, UINT msg, DWORD_PTR instance, DWORD_PTR param1, DWORD_PTR param2)
{
    if (msg == MIM_DATA)
    {
        uint8_t status = param1 & 0xFF;
        uint8_t data1 = (param1 >> 8) & 0xFF;
        uint8_t data2 = (param1 >> 16) & 0xFF;
        if (g_callback)
        {
            g_callback(status, data1, data2, g_user_data);
        }
    }
}

int midi_init(MidiCallback callback, void *user)
{
    if (midiInOpen(&hMidiIn, 0, (DWORD_PTR)MidiInProc, 0, CALLBACK_FUNCTION) != MMSYSERR_NOERROR)
    {
        return -1;
    }
    g_callback = callback;
    g_user_data = user;
    midiInStart(hMidiIn);
    return 0;
}

void midi_close()
{
    if (hMidiIn)
    {
        midiInStop(hMidiIn);
        midiInClose(hMidiIn);
        hMidiIn = NULL;
    }
}
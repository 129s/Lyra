// src/midi.c
#include "midi.h"
#include <stdio.h>

static HMIDIIN hMidiIn;
static Mixer *g_mixer;
static MIDI_Callback g_callback;

static void CALLBACK MidiInProc(HMIDIIN hMidiIn, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
    if (wMsg == MIM_DATA)
    {
        BYTE status = (dwParam1 & 0xFF);
        BYTE data1 = (dwParam1 >> 8) & 0xFF;
        BYTE data2 = (dwParam1 >> 16) & 0xFF;
        g_callback(g_mixer, status, data1, data2);
    }
}

int midi_init(MIDI_Callback callback, Mixer *mixer)
{
    g_callback = callback;
    g_mixer = mixer;
    return midiInOpen(&hMidiIn, 0, (DWORD_PTR)MidiInProc, 0, CALLBACK_FUNCTION);
}

void midi_close()
{
    midiInClose(hMidiIn);
}
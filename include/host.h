
#pragma once
#include <string>
#include "vst2.x/aeffectx.h"
#include "midi.h"
#include <Windows.h>

typedef AEffect *(VSTCALLBACK *VstMainFunc)(audioMasterCallback host);

class VSTHost
{
public:
    VSTHost();
    ~VSTHost();

    bool LoadPlugin(const std::string &dllPath);
    void UnloadPlugin();
    void SendMidiNote(byte note, byte velocity, bool on);
    void ProcessMidiEvents();
    void ProcessAudio(float **inputs, float **outputs, int blockSize);

    int GetSampleRate() const { return sampleRate_; }
    int GetBlockSize() const { return blockSize_; }

private:
    static VSTHost *currentInstance_;
    AEffect *plugin_;
    HINSTANCE dllHandle_;
    MidiEventQueue midiQueue_;
    int sampleRate_;
    int blockSize_;

    VstIntPtr HandleCallback(VstInt32 opcode, VstInt32 index, VstIntPtr value, void *ptr, float opt);
    static VstIntPtr VSTCALLBACK HostCallback(AEffect *effect, VstInt32 opcode, VstInt32 index, VstIntPtr value, void *ptr, float opt);
};
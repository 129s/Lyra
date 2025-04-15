
#pragma once
#include "processor.h"
#include "midi.h"
#include <memory>
typedef unsigned char byte;

class VSTHost
{
public:
    VSTHost();
    ~VSTHost();

    bool LoadPlugin(const std::string &dllPath);  // 原VST加载方式
    void UseProcessor(AudioProcessor *processor); // 新：切换处理器

    void SendMidiNote(byte note, byte velocity, bool on);
    void ProcessMidiEvents();
    void ProcessAudio(float **inputs, float **outputs, int blockSize);

    int GetSampleRate() const { return processor_->GetSampleRate(); }
    int GetBlockSize() const { return processor_->GetBlockSize(); }

private:
    std::unique_ptr<AudioProcessor> processor_;
    MidiEventQueue midiQueue_;
};
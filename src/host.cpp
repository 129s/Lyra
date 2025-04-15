
#include "host.h"
#include "sine_wave.h"

VSTHost::VSTHost()
{
}

VSTHost::~VSTHost()
{
}

void VSTHost::UseProcessor(AudioProcessor *processor)
{
    processor_.reset(processor);
}

void VSTHost::ProcessAudio(float **inputs, float **outputs, int blockSize)
{
    if (processor_)
    {
        processor_->ProcessAudio(outputs[0], outputs[1], blockSize);
    }
}

void VSTHost::SendMidiNote(byte note, byte velocity, bool on)
{
    VstMidiEvent event{};
    event.type = kVstMidiType;
    event.deltaFrames = 0;
    event.midiData[0] = on ? 0x90 : 0x80;
    event.midiData[1] = note;
    event.midiData[2] = velocity;
    midiQueue_.Push(event);
}

void VSTHost::ProcessMidiEvents()
{
    VstMidiEvent event;
    unsigned int frameOffset;
    while (midiQueue_.Pop(event, frameOffset))
    {
        if (processor_)
        {
            processor_->ProcessMidiEvent(event);
        }
    }
}
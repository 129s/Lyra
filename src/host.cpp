#include "host.h"
#include <iostream>
#include <Windows.h>

#define kVstMaxEvents 2400

VSTHost *VSTHost::currentInstance_ = nullptr;

VSTHost::VSTHost()
    : plugin_(nullptr), dllHandle_(nullptr), sampleRate_(44100), blockSize_(512)
{
    currentInstance_ = this;
}

VSTHost::~VSTHost()
{
    UnloadPlugin();
}

bool VSTHost::LoadPlugin(const std::string &dllPath)
{
    dllHandle_ = LoadLibraryA(dllPath.c_str());
    if (!dllHandle_)
    {
        std::cerr << "无法加载DLL: " << dllPath << " (错误: " << GetLastError() << ")" << std::endl;
        return false;
    }

    auto mainEntry = (VstMainFunc)GetProcAddress(dllHandle_, "VSTPluginMain");
    if (!mainEntry)
    {
        std::cerr << "无效的VST入口" << std::endl;
        return false;
    }

    plugin_ = mainEntry(HostCallback);
    if (!plugin_)
    {
        std::cerr << "无法创建插件实例" << std::endl;
        return false;
    }

    plugin_->dispatcher(plugin_, effOpen, 0, 0, 0, 0);
    plugin_->dispatcher(plugin_, effSetSampleRate, 0, 0, 0, static_cast<float>(sampleRate_));
    plugin_->dispatcher(plugin_, effSetBlockSize, 0, blockSize_, 0, 0);
    plugin_->dispatcher(plugin_, effMainsChanged, 0, 1, 0, 0);

    return true;
}

void VSTHost::UnloadPlugin()
{
    if (plugin_)
    {
        plugin_->dispatcher(plugin_, effMainsChanged, 0, 0, 0, 0);
        plugin_->dispatcher(plugin_, effClose, 0, 0, 0, 0);
        plugin_ = nullptr;
    }
    if (dllHandle_)
    {
        FreeLibrary(dllHandle_);
        dllHandle_ = nullptr;
    }
}

void VSTHost::SendMidiNote(byte note, byte velocity, bool on)
{
    VstMidiEvent event{};
    event.type = kVstMidiType;
    event.byteSize = sizeof(VstMidiEvent);
    event.deltaFrames = 0;
    event.midiData[0] = on ? 0x90 : 0x80; // 通道1
    event.midiData[1] = note;
    event.midiData[2] = velocity;
    midiQueue_.Push(event);
}

void VSTHost::ProcessMidiEvents()
{
    VstEvents events{};
    events.numEvents = 0;

    while (events.numEvents < kVstMaxEvents)
    {
        VstMidiEvent event;
        unsigned int frameOffset;
        if (!midiQueue_.Pop(event, frameOffset))
            break;

        VstEvent *vstEvent = new VstEvent;
        memcpy(vstEvent, &event, sizeof(VstMidiEvent));
        events.events[events.numEvents++] = vstEvent;
    }

    if (events.numEvents > 0)
    {
        plugin_->dispatcher(plugin_, effProcessEvents, 0, 0, &events, 0);
        for (int i = 0; i < events.numEvents; ++i)
        {
            delete events.events[i];
        }
    }
}

void VSTHost::ProcessAudio(float **inputs, float **outputs, int blockSize)
{
    if (plugin_ && plugin_->processReplacing)
    {
        plugin_->processReplacing(plugin_, inputs, outputs, blockSize);
    }
}

VstIntPtr VSTCALLBACK VSTHost::HostCallback(AEffect *effect, VstInt32 opcode, VstInt32 index,
                                            VstIntPtr value, void *ptr, float opt)
{
    return currentInstance_->HandleCallback(opcode, index, value, ptr, opt);
}

VstIntPtr VSTHost::HandleCallback(VstInt32 opcode, VstInt32 index,
                                  VstIntPtr value, void *ptr, float opt)
{
    switch (opcode)
    {
    case audioMasterVersion:
        return 2400;

    case audioMasterGetTime:
    {
        static VstTimeInfo timeInfo{};
        timeInfo.samplePos = 0.0;
        timeInfo.sampleRate = sampleRate_;
        timeInfo.flags = kVstTransportPlaying;
        return reinterpret_cast<VstIntPtr>(&timeInfo);
    }

    case audioMasterGetCurrentProcessLevel:
        return kVstProcessLevelRealtime;

    case audioMasterGetProductString:
        strncpy(static_cast<char *>(ptr), "Lyra Host", kVstMaxProductStrLen);
        return 1;

    case audioMasterGetSampleRate:
        return sampleRate_;

    case audioMasterGetBlockSize:
        return blockSize_;

    case audioMasterCanDo:
        if (strcmp(static_cast<const char *>(ptr), "sendVstEvents") == 0 ||
            strcmp(static_cast<const char *>(ptr), "sendVstMidiEvent") == 0)
            return 1;
        return 0;

    default:
        return 0;
    }
}
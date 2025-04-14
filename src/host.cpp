
#include <iostream>
#include <atomic>
#include <vector>
#include <queue>
#include <mutex>
#include <Windows.h>
#include "vst2.x/aeffectx.h"

// 全局变量声明
// ---------------------------------------------------------------
AEffect *g_plugin = nullptr;
HINSTANCE g_dll_handle = nullptr;
std::atomic<bool> g_running{true};

// MIDI事件队列（线程安全）
// ---------------------------------------------------------------
struct MidiEvent
{
    VstMidiEvent event;
    unsigned int frame_offset;
};

class MidiEventQueue
{
private:
    std::queue<MidiEvent> queue_;
    std::mutex mutex_;

public:
    void push(const VstMidiEvent &event, unsigned int frame_offset = 0)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        MidiEvent item{event, frame_offset};
        queue_.push(item);
    }

    bool pop(VstMidiEvent &event, unsigned int &frame_offset)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (queue_.empty())
            return false;

        const auto &item = queue_.front();
        event = item.event;
        frame_offset = item.frame_offset;
        queue_.pop();
        return true;
    }

    void clear()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        while (!queue_.empty())
            queue_.pop();
    }
};

MidiEventQueue g_midi_queue;

// VST宿主回调函数
// ---------------------------------------------------------------
VstIntPtr VSTCALLBACK hostCallback(AEffect *effect, VstInt32 opcode, VstInt32 index, VstIntPtr value, void *ptr, float opt)
{
    switch (opcode)
    {
    case audioMasterVersion:
        return 2400; // 支持VST 2.4

    case audioMasterGetTime:
    {
        auto *timeInfo = new VstTimeInfo{};
        timeInfo->samplePos = 0.0;
        timeInfo->sampleRate = 44100.0;
        timeInfo->flags = kVstTransportPlaying;
        return reinterpret_cast<VstIntPtr>(timeInfo);
    }

    case audioMasterGetCurrentProcessLevel:
        return kVstProcessLevelRealtime; // 实时音频线程

    case audioMasterGetProductString:
        strncpy((char *)ptr, "Lyra Host", kVstMaxProductStrLen);
        return 1;

    default:
        return 0;
    }
}

typedef AEffect *(*VstMainFunc)(audioMasterCallback host);
// VST插件加载与初始化
// ---------------------------------------------------------------
bool LoadVSTPlugin(const char *dllPath)
{
    // 加载DLL
    g_dll_handle = LoadLibraryA(dllPath);
    if (!g_dll_handle)
    {
        printf("错误：%d\n", GetLastError());
        std::cerr << "无法加载DLL: " << dllPath << std::endl;
        return false;
    }

    // 获取入口函数
    auto mainEntry = (VstMainFunc)GetProcAddress(g_dll_handle, "VSTPluginMain");
    if (!mainEntry)
    {
        std::cerr << "无效的VST入口" << std::endl;
        return false;
    }

    // 创建插件实例
    g_plugin = mainEntry(hostCallback);
    if (!g_plugin)
    {
        std::cerr << "无法创建插件实例" << std::endl;
        return false;
    }

    // 初始化插件
    g_plugin->dispatcher(g_plugin, effOpen, 0, 0, 0, 0);
    g_plugin->dispatcher(g_plugin, effSetSampleRate, 0, 0, 0, 44100.0f);
    g_plugin->dispatcher(g_plugin, effSetBlockSize, 0, 512, 0, 0);
    g_plugin->dispatcher(g_plugin, effMainsChanged, 0, 1, 0, 0);

    std::cout << "成功加载插件: " << dllPath << std::endl;
    return true;
}

// MIDI消息发送函数
// ---------------------------------------------------------------
void SendMidiNote(byte note, byte velocity, bool on)
{
    VstMidiEvent event;
    memset(&event, 0, sizeof(VstMidiEvent));
    event.type = kVstMidiType;
    event.byteSize = sizeof(VstMidiEvent);
    event.deltaFrames = 0;
    event.midiData[0] = on ? 0x90 : 0x80; // 通道1（注意VST通道从0开始）
    event.midiData[1] = note;
    event.midiData[2] = velocity;

    g_midi_queue.push(event);
}

int test()
{
    printf("加载Pianoteq\n");
    // 加载Pianoteq
    if (!LoadVSTPlugin("L:\\CppProject\\Lyra\\plugin\\Pianoteq 6.dll"))
    {
        return 1;
    }

    // 交互测试
    std::cout << "按回车键播放C大调和弦，按q退出..." << std::endl;
    while (g_running)
    {
        int c = std::cin.get();

        if (c == 'q')
            break;

        // 发送C大三和弦
        SendMidiNote(60, 100, true); // C4
        SendMidiNote(64, 100, true); // E4
        SendMidiNote(67, 100, true); // G4
        Sleep(1000);
        SendMidiNote(60, 0, false);
        SendMidiNote(64, 0, false);
        SendMidiNote(67, 0, false);
    }

    // 清理

    if (g_plugin)
    {
        g_plugin->dispatcher(g_plugin, effMainsChanged, 0, 0, 0, 0);
        g_plugin->dispatcher(g_plugin, effClose, 0, 0, 0, 0);
    }
    if (g_dll_handle)
        FreeLibrary(g_dll_handle);

    return 0;
}
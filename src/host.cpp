#include "host.h"
#include <iostream>
#include <Windows.h>

#define kVstMaxEvents 2048 // 定义最大VST事件数量

// 静态成员变量初始化
VSTHost *VSTHost::currentInstance_ = nullptr;

// 构造函数
VSTHost::VSTHost()
    : plugin_(nullptr), dllHandle_(nullptr), sampleRate_(44100), blockSize_(512)
{
    currentInstance_ = this; // 设置当前实例指针
}

// 析构函数
VSTHost::~VSTHost()
{
    UnloadPlugin(); // 卸载插件
}

// 加载VST插件
bool VSTHost::LoadPlugin(const std::string &dllPath)
{
    // 加载DLL
    dllHandle_ = LoadLibraryA(dllPath.c_str());
    if (!dllHandle_)
    {
        std::cerr << "无法加载DLL: " << dllPath << " (错误: " << GetLastError() << ")" << std::endl;
        return false;
    }

    // 获取VST插件入口点
    auto mainEntry = (VstMainFunc)GetProcAddress(dllHandle_, "VSTPluginMain");
    if (!mainEntry)
    {
        std::cerr << "无效的VST入口" << std::endl;
        return false;
    }

    // 创建插件实例
    plugin_ = mainEntry(HostCallback);
    if (!plugin_)
    {
        std::cerr << "无法创建插件实例" << std::endl;
        return false;
    }

    // 初始化插件
    plugin_->dispatcher(plugin_, effOpen, 0, 0, 0, 0);                                        // 打开插件
    plugin_->dispatcher(plugin_, effSetSampleRate, 0, 0, 0, static_cast<float>(sampleRate_)); // 设置采样率
    plugin_->dispatcher(plugin_, effSetBlockSize, 0, blockSize_, 0, 0);                       // 设置块大小
    plugin_->dispatcher(plugin_, effMainsChanged, 0, 1, 0, 0);                                // 激活插件

    return true;
}

// 卸载VST插件
void VSTHost::UnloadPlugin()
{
    // 关闭插件
    if (plugin_)
    {
        plugin_->dispatcher(plugin_, effMainsChanged, 0, 0, 0, 0); // 停用插件
        plugin_->dispatcher(plugin_, effClose, 0, 0, 0, 0);        // 关闭插件
        plugin_ = nullptr;                                         // 重置插件指针
    }

    // 释放DLL
    if (dllHandle_)
    {
        FreeLibrary(dllHandle_); // 释放DLL
        dllHandle_ = nullptr;    // 重置DLL句柄
    }
}

// 发送MIDI音符事件
void VSTHost::SendMidiNote(byte note, byte velocity, bool on)
{
    VstMidiEvent event{};
    event.type = kVstMidiType;             // 设置事件类型为MIDI
    event.byteSize = sizeof(VstMidiEvent); // 设置事件大小
    event.deltaFrames = 0;                 // 设置帧偏移量为0
    event.midiData[0] = on ? 0x90 : 0x80;  // 设置MIDI状态字节（音符开/关，通道1）
    event.midiData[1] = note;              // 设置音符
    event.midiData[2] = velocity;          // 设置力度
    midiQueue_.Push(event);                // 将MIDI事件推入队列
}

// 处理MIDI事件
void VSTHost::ProcessMidiEvents()
{
    const int maxEventsToProcess = kVstMaxEvents;
    std::vector<VstMidiEvent *> midiEvents;

    // 步骤1：收集所有待处理事件
    while (midiEvents.size() < maxEventsToProcess)
    {
        VstMidiEvent midiEvent;
        unsigned int frameOffset;
        if (!midiQueue_.Pop(midiEvent, frameOffset))
            break;

        // 分配并填充事件
        VstMidiEvent *vstMidiEvent = new VstMidiEvent;
        *vstMidiEvent = midiEvent;
        vstMidiEvent->type = kVstMidiType;
        vstMidiEvent->byteSize = sizeof(VstMidiEvent);
        vstMidiEvent->deltaFrames = frameOffset;
        midiEvents.push_back(vstMidiEvent);
    }

    if (midiEvents.empty())
        return;

    // 步骤2：动态分配VstEvents结构
    const size_t eventsSize = sizeof(VstEvents) + (midiEvents.size() - 1) * sizeof(VstEvent *);
    VstEvents *events = reinterpret_cast<VstEvents *>(new char[eventsSize]);
    events->numEvents = static_cast<VstInt32>(midiEvents.size());
    events->reserved = 0;

    // 填充事件指针
    for (size_t i = 0; i < midiEvents.size(); ++i)
    {
        events->events[i] = reinterpret_cast<VstEvent *>(midiEvents[i]);
    }

    // 步骤3：发送事件给插件
    plugin_->dispatcher(plugin_, effProcessEvents, 0, 0, events, 0);

    // 步骤4：清理内存
    for (auto *event : midiEvents)
    {
        delete event;
    }
    delete[] reinterpret_cast<char *>(events);
}

// 处理音频
void VSTHost::ProcessAudio(float **inputs, float **outputs, int blockSize)
{
    // 如果插件存在且支持processReplacing，则调用processReplacing
    if (plugin_ && plugin_->processReplacing)
    {
        plugin_->processReplacing(plugin_, inputs, outputs, blockSize); // 调用插件的音频处理函数
    }
}

// VST宿主回调函数
VstIntPtr VSTCALLBACK VSTHost::HostCallback(AEffect *effect, VstInt32 opcode, VstInt32 index,
                                            VstIntPtr value, void *ptr, float opt)
{
    // 调用实例的HandleCallback函数
    return currentInstance_->HandleCallback(opcode, index, value, ptr, opt);
}

// 处理宿主回调
VstIntPtr VSTHost::HandleCallback(VstInt32 opcode, VstInt32 index,
                                  VstIntPtr value, void *ptr, float opt)
{
    // 根据opcode处理不同的宿主请求
    switch (opcode)
    {
    case audioMasterVersion:
        return 2400; // 返回VST版本

    case audioMasterGetTime:
    {
        // 返回时间信息
        static VstTimeInfo timeInfo{};
        timeInfo.samplePos = 0.0;                      // 设置采样位置
        timeInfo.sampleRate = sampleRate_;             // 设置采样率
        timeInfo.flags = kVstTransportPlaying;         // 设置标志为播放中
        return reinterpret_cast<VstIntPtr>(&timeInfo); // 返回时间信息指针
    }

    case audioMasterGetCurrentProcessLevel:
        return kVstProcessLevelRealtime; // 返回实时处理级别

    case audioMasterGetProductString:
        strncpy(static_cast<char *>(ptr), "Lyra Host", kVstMaxProductStrLen); // 返回产品字符串
        return 1;

    case audioMasterGetSampleRate:
        return sampleRate_; // 返回采样率

    case audioMasterGetBlockSize:
        return blockSize_; // 返回块大小

    case audioMasterCanDo:
        // 检查插件是否支持特定功能
        if (strcmp(static_cast<const char *>(ptr), "sendVstEvents") == 0 ||
            strcmp(static_cast<const char *>(ptr), "sendVstMidiEvent") == 0)
            return 1; // 支持发送VST事件和MIDI事件
        return 0;     // 不支持

    default:
        return 0; // 未知opcode
    }
}
#include "midi.h"

// 将MIDI事件推入队列
void MidiEventQueue::Push(const VstMidiEvent &event, unsigned int frame_offset)
{
    std::lock_guard<std::mutex> lock(mutex_); // 加锁，保证线程安全
    queue_.push({event, frame_offset});       // 将MIDI事件和帧偏移量推入队列
}

// 从队列中弹出MIDI事件
bool MidiEventQueue::Pop(VstMidiEvent &event, unsigned int &frame_offset)
{
    std::lock_guard<std::mutex> lock(mutex_); // 加锁，保证线程安全
    if (queue_.empty())
        return false; // 如果队列为空，则返回false

    const auto &item = queue_.front(); // 获取队列头部元素
    event = item.event;                // 复制MIDI事件
    frame_offset = item.frame_offset;  // 复制帧偏移量
    queue_.pop();                      // 从队列中移除元素
    return true;                       // 返回true
}

// 清空MIDI事件队列
void MidiEventQueue::Clear()
{
    std::lock_guard<std::mutex> lock(mutex_); // 加锁，保证线程安全
    while (!queue_.empty())
        queue_.pop(); // 循环弹出队列中的所有元素
}
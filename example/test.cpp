#include "host.h"
#include "audio.h"
#include "sine_wave.h"
#include <iostream>
#include <random>

std::atomic<bool> running{true};

int main()
{
    VSTHost host;

    host.UseProcessor(new SineWaveProcessor(44100, 512));

    AudioOutput audio(host);
    if (!audio.Initialize())
        return 1;

    audio.Start();

    // 添加全局事件间隔控制
    constexpr std::chrono::milliseconds NOTE_DURATION = std::chrono::milliseconds(125); // 音符持续时间

    while (running)
    {
        // 生成随机音符
        static std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<int> dist(36, 84);
        int note = dist(gen);

        // 发送Note On
        host.SendMidiNote(note, 100, true);
        std::cout << "Play note: " << note << "\n"; // 换用\n提升性能

        // 等待音符持续时间
        auto start = std::chrono::steady_clock::now();
        while (std::chrono::steady_clock::now() - start < NOTE_DURATION)
        {
            continue;
        }

        // 发送Note Off
        host.SendMidiNote(note, 0, false);
    }
}
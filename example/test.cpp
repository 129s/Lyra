#include "host.h"
#include "audio.h"
#include "sine_wave.h"
#include <iostream>
#include <random>
#include <vector>
#include <map>

std::atomic<bool> running{true};

// 五声音阶音符 (C大调五声音阶: C4-D4-E4-G4-A4)
const std::vector<int> pentatonic_scale = {60, 62, 64, 67, 69};

// 随机数生成
std::random_device rd;
std::mt19937 gen(rd());

int main()
{
    VSTHost host;
    SineWaveProcessor osc(44100, 512);
    osc.SetEnvelope(50.0f, 50.0f); // 攻击50ms，释放200ms
    host.UseProcessor(&osc);
    AudioOutput audio(host);

    if (!audio.Initialize())
        return 1;

    audio.Start();

    // 旋律参数
    constexpr auto MELODY_INTERVAL = std::chrono::milliseconds(200);
    constexpr auto MELODY_INTERVAL2 = std::chrono::milliseconds(100);
    std::uniform_int_distribution<int> melody_dist(0, pentatonic_scale.size() - 1);

    auto last_melody_time = std::chrono::steady_clock::now() - MELODY_INTERVAL;

    // while (running)
    {
        auto now = std::chrono::steady_clock::now();

        // 处理旋律
        if (now - last_melody_time >= MELODY_INTERVAL)
        {
            // 随机选择五声音阶音符（提高一个八度）
            int note = pentatonic_scale[melody_dist(gen)] + 12;
            int note3 = pentatonic_scale[melody_dist(gen)] + 12;
            int note2 = pentatonic_scale[melody_dist(gen)];

            // 触发旋律音符
            host.SendMidiNote(note, 40, true);
            host.SendMidiNote(note2, 40, true);
            host.SendMidiNote(note3, 40, true);
            std::cout << "旋律音符: " << note << std::endl;

            std::this_thread::sleep_for(MELODY_INTERVAL2);
            host.SendMidiNote(note3, 0, false);
            host.SendMidiNote(note2, 0, false);
            host.SendMidiNote(note, 0, false);

            last_melody_time = now;
        }
    }

    audio.Stop();
    return 0;
}
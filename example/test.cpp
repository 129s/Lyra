#include "host.h"
#include "audio.h"
#include "sine_wave.h"
#include <iostream>
#include <random>
#include <vector>
#include <map>

std::atomic<bool> running{true};

// 和弦定义 (C大调4536进行)
const std::vector<std::vector<int>> chord_progression = {
    {65, 69, 72}, // F大三和弦 (IV)
    {67, 71, 74}, // G大三和弦 (V)
    {64, 67, 71}, // Em小三和弦 (III-)
    {69, 72, 76}  // Am小三和弦 (VI-)
};

// 五声音阶音符 (C大调五声音阶: C4-D4-E4-G4-A4)
const std::vector<int> pentatonic_scale = {60, 62, 64, 67, 69};

// 随机数生成
std::random_device rd;
std::mt19937 gen(rd());

void PlayChord(VSTHost &host, const std::vector<int> &notes, int velocity, bool on)
{
    for (int note : notes)
    {
        host.SendMidiNote(note, velocity, on);
    }
}

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

    // 和弦循环参数
    size_t current_chord = 0;
    constexpr auto CHORD_DURATION = std::chrono::milliseconds(2000); // 每个和弦2秒

    // 旋律参数
    constexpr auto MELODY_INTERVAL = std::chrono::milliseconds(250); // 每250ms触发一个音符
    std::uniform_int_distribution<int> melody_dist(0, pentatonic_scale.size() - 1);

    auto last_chord_time = std::chrono::steady_clock::now();
    auto last_melody_time = last_chord_time;

    while (running)
    {
        auto now = std::chrono::steady_clock::now();

        // 处理和弦切换
        if (now - last_chord_time >= CHORD_DURATION)
        {
            // 关闭旧和弦
            PlayChord(host, chord_progression[current_chord], 0, false);

            // 切换到下一个和弦
            current_chord = (current_chord + 1) % chord_progression.size();

            // 触发新和弦
            PlayChord(host, chord_progression[current_chord], 20, true);

            last_chord_time = now;
            std::cout << "和弦切换至: " << (current_chord + 1) << std::endl;
        }

        // 处理旋律
        if (now - last_melody_time > MELODY_INTERVAL)
        {
            // 随机选择五声音阶音符（提高一个八度）
            int note = pentatonic_scale[melody_dist(gen)] + 12;

            // 用较高力度触发旋律音符
            host.SendMidiNote(note, 30, true);
            std::cout << "旋律音符: " << note << std::endl;

            // 设置1/4音符后释放
            std::thread([MELODY_INTERVAL, &host, note]()
                        {
                std::this_thread::sleep_for(MELODY_INTERVAL);
                host.SendMidiNote(note, 0, false); })
                .detach();

            last_melody_time = now;
        }
    }

    // 停止所有音符
    for (const auto &chord : chord_progression)
    {
        PlayChord(host, chord, 0, false);
    }

    audio.Stop();
    return 0;
}
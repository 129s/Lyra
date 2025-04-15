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

    constexpr auto NOTE_DURATION = std::chrono::milliseconds(120);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 9);

    while (true)
    {
        int pentatonic_scale[10] = {
            70,
            72,
            75,
            77,
            79,
            82,
            84,
            87,
            89,
            91,
        };
        int note = pentatonic_scale[dist(gen)];
        note -= 4;
        std::cout << "▶ Play note: " << note << std::endl;

        host.SendMidiNote(note, 100, true);
        std::this_thread::sleep_for(NOTE_DURATION);
        host.SendMidiNote(note, 0, false);
    }

    audio.Stop();
    return 0;
}
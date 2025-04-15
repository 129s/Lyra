#include "host.h"
#include "audio.h"
#include "sine_wave.h"
#include <iostream>
#include <random>

std::atomic<bool> running{true};

int main()
{
    VSTHost host;
    SineWaveProcessor osc = SineWaveProcessor(44100, 512);
    osc.SetEnvelope(25.0f, 25.0f);
    host.UseProcessor(&osc);
    AudioOutput audio(host);
    if (!audio.Initialize())
        return 1;

    audio.Start();

    constexpr auto NOTE_DURATION_BASE = 400;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 9);

    int i = 0;

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
        int velocity = 25 * (++i % 4 + 1);
        auto duration = std::chrono::milliseconds(NOTE_DURATION_BASE / 4);
        note -= 4;
        std::cout << "Play note: " << note << " vel: " << velocity << "\n";

        host.SendMidiNote(note, velocity / 2, true);
        // host.SendMidiNote(note - 12, velocity / 2, true);
        std::this_thread::sleep_for(duration);
        host.SendMidiNote(note, 0, false);
        // host.SendMidiNote(note - 12, velocity / 2, false);
    }

    audio.Stop();
    return 0;
}
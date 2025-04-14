#include "host.h"
#include "audio.h"
#include <iostream>
#include <atomic>
#include <stdlib.h>

std::atomic<bool> running{true};

int main()
{
    VSTHost host;
    AudioOutput audio(host);

    if (!host.LoadPlugin("L:\\CppProject\\Lyra\\plugin\\Pianoteq 6.dll") || !audio.Initialize())
        return 1;

    audio.Start();

    std::cout << "Press Enter to play...";
    std::cin.get();
    host.SendMidiNote(60, 100, true);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    host.SendMidiNote(60, 0, false);

    running = false;
    audio.Stop();
    return 0;
}
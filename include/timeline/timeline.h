#pragma once
#include <vector>
#include <memory>
#include <atomic>
#include <thread>
#include <mutex>
#include "event.h"
#include <algorithm>

class Timeline
{
public:
    Timeline(int ppq = 480) : ppq_(ppq), running_(false) {}

    void add_event(std::unique_ptr<Event> event)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        events_.push_back(std::move(event));
        sort_events();
    }

    void play()
    {
        if (running_)
            return;
        running_ = true;
        thread_ = std::thread([this]
                              { playback_loop(); });
    }

    void stop()
    {
        running_ = false;
        if (thread_.joinable())
            thread_.join();
    }

    void continue_play()
    {
        if (!running_)
            play();
    }

    void set_tempo(float bpm)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        tick_duration_ = 60000.0f / (bpm * ppq_);
    }

private:
    void playback_loop()
    {
        uint64_t start_time = get_current_time();
        uint64_t current_tick = 0;

        while (running_)
        {
            process_events(current_tick);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            current_tick = (get_current_time() - start_time) / tick_duration_;
        }
    }

    void process_events(uint64_t current_tick)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = events_.begin();
        while (it != events_.end())
        {
            if ((*it)->is_complete(current_tick))
            {
                (*it)->trigger(current_tick);
                it = events_.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    void sort_events()
    {
        std::sort(events_.begin(), events_.end(),
                  [](const auto &a, const auto &b)
                  {
                      return a->get_tick() < b->get_tick();
                  });
    }

    uint64_t get_current_time() const
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::steady_clock::now().time_since_epoch())
            .count();
    }

    std::vector<std::unique_ptr<Event>> events_;
    std::mutex mutex_;
    std::thread thread_;
    std::atomic<bool> running_;
    float tick_duration_ = 1.0f;
    const int ppq_; // 每四分音符的tick数
};
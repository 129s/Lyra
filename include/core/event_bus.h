
#pragma once
#include <functional>
#include <unordered_map>
#include <queue>
#include <vector>
#include <memory>
#include <typeinfo>
#include <typeindex>
#include "event.h"

class EventBus
{
public:
    using EventHandler = std::function<void(const Event &)>;

    template <typename T>
    void Subscribe(EventHandler handler)
    {
        subscribers_[T::EventTypeID].push_back(handler);
    }

    template <typename T>
    void Publish(const T &event)
    {
        auto type = T::EventTypeID;
        if (subscribers_.find(type) != subscribers_.end())
        {
            for (auto &handler : subscribers_[type])
            {
                handler(event);
            }
        }
    }

    void QueueEvent(std::unique_ptr<Event> event)
    {
        eventQueue_.push(std::move(event));
    }

    void DispatchEvents()
    {
        while (!eventQueue_.empty())
        {
            auto event = std::move(eventQueue_.front());
            Publish(*event);
            eventQueue_.pop();
        }
    }

private:
    std::unordered_map<uint32_t, std::vector<EventHandler>> subscribers_;
    std::queue<std::unique_ptr<Event>> eventQueue_;
};
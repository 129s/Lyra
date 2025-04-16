
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

    // 订阅事件类型（模板化以支持多态）
    template <typename T>
    void Subscribe(EventHandler handler)
    {
        subscribers_[typeid(T)].push_back(handler);
    }

    // 发布事件（支持多态派生类）
    void Publish(const Event &event)
    {
        auto type = typeid(event);
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
        std::lock_guard lock(queueMutex_);
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
    std::unordered_map<std::type_index, std::vector<EventHandler>> subscribers_;
    std::queue<std::unique_ptr<Event>> eventQueue_;
};

#pragma once
#include <functional>
#include <unordered_map>
#include <vector>
#include <typeinfo>
#include <typeindex>
#include "core/event.h" // 原有 Event 基类

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

private:
    std::unordered_map<std::type_index, std::vector<EventHandler>> subscribers_;
};
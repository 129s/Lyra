#pragma once
#include <cstdint>

class Event
{
public:
    virtual ~Event() = default;
    virtual void trigger(uint64_t current_tick) = 0;
    virtual uint64_t get_tick() const = 0;
    virtual bool is_complete(uint64_t current_tick) const = 0;
};
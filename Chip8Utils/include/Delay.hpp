#pragma once

#include <cassert>
#include <exception>
#include <thread>

namespace Chip8::Utils
{
    constexpr int FpsDelayNs(const int fps)
    {
        if (fps <= 0) {
            throw std::logic_error("fps can't be zero or negative!");
        }
        const double delayMs = 1000.0 / fps;
        const int ns = static_cast<int>(delayMs) * 1000000;
        return ns;
    }

    inline void WaitNs(const int delay)
    {
        assert(delay > 0);
        std::this_thread::sleep_for(std::chrono::nanoseconds(delay));
    }
}

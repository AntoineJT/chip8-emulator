// Derived from the original
// https://github.com/99x/timercpp
#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <functional>

class Timer {
    std::atomic<bool> active = true;

    template <typename Duration>
    void _setInterval(std::function<void()> function, int interval)
    {
        active = true;
        std::thread t([=]() {
            while (active.load()) {
                std::this_thread::sleep_for(Duration(interval));
                if (!active.load()) return;
                function();
            }
        });
        t.detach();
    }

    public:
        void setTimeout(std::function<void()> function, int delay);
        void setInterval(std::function<void()> function, int interval);
        void setIntervalNs(std::function<void()> function, int interval);
        void stop();
};

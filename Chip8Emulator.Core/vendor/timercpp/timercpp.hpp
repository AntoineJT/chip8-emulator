// Derived from the original
// https://github.com/99x/timercpp
// commit: fbf911046b46f4fa68e3a94d004acb3d9de41f10
#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <functional>
#include <type_traits>

class Timer {
    std::atomic<bool> active = true;

    template <typename Duration>
    void _setInterval(const std::function<void()>& function, int interval)
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
        void setTimeout(const std::function<void()>& function, int delay);
        void setInterval(const std::function<void()>& function, int interval);
        void setIntervalNs(const std::function<void()>& function, int interval);
        void stop();
};

// Derived from the original
// https://github.com/99x/timercpp
#include "timercpp.h"

void Timer::setTimeout(std::function<void()> function, int delay) {
    active = true;
    std::thread t([=]() {
        if(!active.load()) return;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        if(!active.load()) return;
        function();
    });
    t.detach();
}

void Timer::setInterval(std::function<void()> function, int interval) {
    active = true;
    std::thread t([=]() {
        while(active.load()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
            if(!active.load()) return;
            function();
        }
    });
    t.detach();
}

void Timer::setIntervalNs(std::function<void()> function, int interval) {
    active = true;
    std::thread t([=]() {
        while (active.load()) {
            std::this_thread::sleep_for(std::chrono::nanoseconds(interval));
            if (!active.load()) return;
            function();
        }
        });
    t.detach();
}

void Timer::stop() {
    active = false;
}

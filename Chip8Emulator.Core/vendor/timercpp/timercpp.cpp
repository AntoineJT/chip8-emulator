// Derived from the original
// https://github.com/99x/timercpp
// commit: fbf911046b46f4fa68e3a94d004acb3d9de41f10
#include "timercpp.hpp"

#include <utility>

void Timer::setTimeout(const std::function<void()>& function, int delay)
{
    active = true;
    std::thread t([=]() {
        if(!active.load()) return;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        if(!active.load()) return;
        function();
    });
    t.detach();
}

void Timer::setInterval(std::function<void()> function, int interval)
{
    _setInterval<std::chrono::milliseconds>(std::move(function), interval);
}

void Timer::setIntervalNs(std::function<void()> function, int interval)
{
    _setInterval<std::chrono::nanoseconds>(std::move(function), interval);
}

void Timer::stop()
{
    active = false;
}

// Derived from the original
// https://github.com/99x/timercpp
#include "timercpp.hpp"
#include <type_traits>

void Timer::setTimeout(std::function<void()> function, int delay)
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
    _setInterval<std::chrono::milliseconds>(function, interval);
}

void Timer::setIntervalNs(std::function<void()> function, int interval)
{
    _setInterval<std::chrono::nanoseconds>(function, interval);
}

void Timer::stop()
{
    active = false;
}

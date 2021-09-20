// Derived from the original
// https://github.com/99x/timercpp
// commit: fbf911046b46f4fa68e3a94d004acb3d9de41f10
#include "timercpp.hpp"

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

void Timer::setInterval(const std::function<void()>& function, int interval)
{
    _setInterval<std::chrono::milliseconds>(function, interval);
}

void Timer::setIntervalNs(const std::function<void()>& function, int interval)
{
    _setInterval<std::chrono::nanoseconds>(function, interval);
}

void Timer::stop()
{
    active = false;
}

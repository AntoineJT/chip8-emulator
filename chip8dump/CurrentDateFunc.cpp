#include "CurrentDateFunc.hpp"

#include <ctime>
#include <string>

std::string CurrentDate() noexcept
{
    constexpr std::size_t buffer_size = 50;
    auto* buffer = new char[buffer_size];

    const std::time_t time = std::time(nullptr);
    std::strftime(buffer, buffer_size, "%Y_%m_%d-%H_%M_%S", std::localtime(&time));

    std::string date(buffer);
    delete[] buffer;

    return date;
}

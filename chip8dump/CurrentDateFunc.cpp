#include "CurrentDateFunc.hpp"

#include <ctime>
#include <string>

std::string CurrentDate() noexcept
{
    constexpr std::size_t buffer_size = 50;
    std::string date(buffer_size, ' ');

    const std::time_t time = std::time(nullptr);
    const std::size_t size = std::strftime(date.data(), buffer_size, "%Y_%m_%d-%H_%M_%S", std::localtime(&time));
    date.resize(size);

    return date;
}

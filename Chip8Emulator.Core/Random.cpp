#include "Random.hpp"

Chip8::Random::Random(const int min, const int max)
    : min(min)
    , max(max)
{}

int Chip8::Random::Pick() const
{
    static auto dist = std::uniform_int_distribution<int>(min, max);
    return dist(gen);
}

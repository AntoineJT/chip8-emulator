#include "Random.hpp"

Chip8::Random::Random(const int min, const int max)
    : min(min)
    , max(max)
    , dist(min, max)
{}

int Chip8::Random::Pick() const
{
    return dist(gen);
}

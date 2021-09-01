#pragma once
#include <random>

namespace Chip8
{
    class Random
    {
        static inline std::random_device rd {};
        static inline std::mt19937 gen{ rd() };
        const int min;
        const int max;

    public:
        Random(int min, int max);
        int Pick() const;
    };
}

#pragma once

#include <cstdint>
#include <sdl.hpp>

namespace Chip8
{
    // Chip8 Base screen size
    constexpr int base_width = 64;
    constexpr int base_height = 32;

    class Screen
    {
        uint8_t m_ratio;
    public:
        explicit Screen(SDL2::SDL& sdl, uint8_t ratio);
        //bool DrawPoint();
    };
};

#pragma once

#include <sdl.hpp>

namespace Chip8
{
    // Chip8 Base screen size
    constexpr int base_width = 64;
    constexpr int base_height = 32;

    class Screen
    {
    public:
        explicit Screen(SDL2::SDL& sdl, int width, int height);
    };
};

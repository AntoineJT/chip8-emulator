#pragma once

#include <array>
#include <cstdint>
#include <sdl.hpp>

#include "sdl_renderer.hpp"
#include "sdl_window.hpp"

namespace Chip8
{
    // Chip8 Base screen size
    constexpr std::size_t base_width = 64;
    constexpr std::size_t base_height = 32;

    class Screen
    {
        uint8_t m_ratio;
        SDL2::Window m_window;
        SDL2::Renderer m_renderer;
    public:
        using Pixel = bool;
        using PixelGrid = std::array<std::array<Pixel, base_width>, base_height>;

        explicit Screen(SDL2::SDL& sdl, uint8_t ratio);
        bool DrawPoints(PixelGrid grid) const;
        bool DrawPoints(SDL_Color color, std::vector<SDL_Rect> rects) const;
        void Refresh(bool fullRefresh) const;
    };
};

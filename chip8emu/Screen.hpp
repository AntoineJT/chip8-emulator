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

    struct Screen
    {
        using PixelGrid = std::array<std::array<bool, base_width>, base_height>;
        using Point = std::pair<uint8_t, uint8_t>;

        explicit Screen(SDL2::SDL& sdl, std::uint8_t ratio);
        void Render(PixelGrid grid) const;
        void DrawPoints(SDL_Color color, std::vector<SDL_Rect> rects) const;
        void DrawSprite(std::vector<Point> pixelsOn);
        void Refresh(bool fullRefresh);
        void ChangeBgColor(SDL_Color color, bool fullRefresh);
        bool Collides(uint8_t x, uint8_t y) const;

    private:
        std::uint8_t m_ratio;
        PixelGrid m_grid;
        SDL2::Window m_window;
        SDL2::Renderer m_renderer;

        static void ResetGrid(PixelGrid& grid);
        static PixelGrid InitGrid();
    };
};

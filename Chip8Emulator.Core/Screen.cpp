#include "include/Screen.hpp"

#include <array>
#include <cassert>
#include <cstdint>

#include "sdl.hpp"
#include "sdl_assert.h"
#include "sdl_renderer.hpp"
#include "sdl_window.hpp"

SDL2::Window CreateWindow(const SDL2::SDL& sdl, const std::uint8_t ratio) noexcept
{
    assert(sdl.Running());

    const int width = static_cast<int>(Chip8::base_width) * ratio;
    const int height = static_cast<int>(Chip8::base_height) * ratio;

    return SDL2::Window("Chip8Emu",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height, 0);
}

void Chip8::Screen::ResetGrid(PixelGrid& grid) noexcept
{
    for (std::size_t y = 0; y < base_height; ++y)
    {
        grid[y].fill(false);
    }
}

Chip8::Screen::PixelGrid Chip8::Screen::InitGrid() noexcept
{
    PixelGrid grid;
    ResetGrid(grid);
    return grid;
}

Chip8::Screen::Screen(const SDL2::SDL& sdl, const std::uint8_t ratio) noexcept
    : m_ratio(ratio)
    , m_window(CreateWindow(sdl, ratio))
    , m_renderer(SDL2::Renderer(m_window, -1, SDL_RENDERER_ACCELERATED))
{}

void Chip8::Screen::DrawPoints(const SDL_Color color, const std::vector<SDL_Rect>& rects) const noexcept
{
    // virtual method
}

void Chip8::Screen::DrawSprite(const std::vector<Point>& pixelsOn)
{
}

bool Chip8::Screen::Collides(const uint8_t x, const uint8_t y) const noexcept
{
    assert(x >= 0 && x <= base_width);
    assert(y >= 0 && y <= base_height);
    return m_grid[x][y];
}

void Chip8::Screen::Refresh(const bool fullRefresh) noexcept
{
    // virtual method
}

void Chip8::Screen::Render(const PixelGrid& grid) const
{
    // virtual method
}

void Chip8::Screen::ChangeBgColor(const SDL_Color color, const bool fullRefresh) noexcept
{
    // virtual method
}

#include "Screen.hpp"

#include <array>
#include <cassert>
#include <cstdint>

#include "sdl.hpp"
#include "sdl_assert.h"
#include "sdl_colors.hpp"
#include "sdl_renderer.hpp"
#include "sdl_window.hpp"

SDL2::Window CreateWindow(std::shared_ptr<SDL2::SDL> sdl, const std::uint8_t ratio)
{
    assert((*sdl.get()).Running());

    const int width = static_cast<int>(Chip8::base_width) * ratio;
    const int height = static_cast<int>(Chip8::base_height) * ratio;

    return SDL2::Window("Chip8Emu",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height, 0);
}

void Chip8::Screen::ResetGrid(PixelGrid& grid)
{
    for (std::size_t y = 0; y < base_height; ++y)
    {
        grid[y].fill(false);
    }
}

Chip8::Screen::PixelGrid Chip8::Screen::InitGrid()
{
    PixelGrid grid;
    ResetGrid(grid);
    return grid;
}

Chip8::Screen::Screen(std::shared_ptr<SDL2::SDL> sdl, const std::uint8_t ratio)
    : m_sdl(sdl)
    , m_ratio(ratio)
    , m_window(CreateWindow(sdl, ratio))
    , m_renderer(SDL2::Renderer(m_window, -1, SDL_RENDERER_ACCELERATED))
{
    // set background to black
    m_renderer.SetDrawColor(SDL2::Colors::BLACK);
    // a full refresh is required here to draw the black bg
    Refresh(true);
}

// this will be used for internal splashscreen for example
void Chip8::Screen::Render(const PixelGrid& grid)
{
    std::vector<SDL_Rect> pixelsOff;
    std::vector<SDL_Rect> pixelsOn;

    for (size_t y = 0; y < base_height; ++y)
    {
        for (size_t x = 0; x < base_width; ++x)
        {
            const bool isOn = grid[y][x];
            const SDL_Rect rect = {
                static_cast<int>(x) * m_ratio,
                static_cast<int>(y) * m_ratio,
                m_ratio,
                m_ratio
            };

            (isOn ? pixelsOn : pixelsOff).push_back(rect);
        }
    }

    DrawPoints(SDL2::Colors::BLACK, pixelsOff);
    DrawPoints(SDL2::Colors::WHITE, pixelsOn);
}

void Chip8::Screen::DrawPoints(const SDL_Color color, const std::vector<SDL_Rect>& rects)
{
    m_renderer.SetDrawColor(color);
    m_renderer.FillRects(rects);
}

void Chip8::Screen::DrawSprite(const std::vector<Point>& pixelsOn)
{
    assert(!pixelsOn.empty());

    std::vector<SDL_Rect> rects; // (pixelsOn.size());
    for (const auto& pt : pixelsOn)
    {
        m_grid[pt.second][pt.first] ^= true;
        const SDL_Rect rect = {
            static_cast<int>(pt.first) * m_ratio,
            static_cast<int>(pt.second) * m_ratio,
            m_ratio,
            m_ratio
        };
        rects.push_back(rect);
    }
    DrawPoints(SDL2::Colors::WHITE, rects);
}

void Chip8::Screen::Refresh(const bool fullRefresh)
{
    if (fullRefresh)
    {
        // clears screen
        m_renderer.RenderClear();
        // clears grid cache
        ResetGrid(m_grid);
    }
    // renders screen
    m_renderer.RenderPresent();
}

void Chip8::Screen::ChangeBgColor(const SDL_Color color, const bool fullRefresh)
{
    m_renderer.SetDrawColor(color);
    Refresh(fullRefresh);
}

bool Chip8::Screen::Collides(const uint8_t x, const uint8_t y) const
{
    assert(x >= 0 && x <= base_width);
    assert(y >= 0 && y <= base_height);
    return m_grid[x][y];
}

#include "Screen.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>

#include "sdl.hpp"
#include "sdl_assert.hpp"
#include "sdl_colors.hpp"
#include "sdl_renderer.hpp"
#include "sdl_window.hpp"

SDL2::Window CreateWindow(const SDL2::SDL& sdl, std::uint8_t ratio)
{
    assert(sdl.Running());

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

Chip8::Screen::Screen(const SDL2::SDL& sdl, std::uint8_t ratio)
    : m_ratio(ratio)
    , m_grid(InitGrid())
    , m_window(CreateWindow(sdl, ratio))
    , m_renderer(SDL2::Renderer(m_window, -1, SDL_RENDERER_ACCELERATED))
{
    // set background to black
    sdl_assert(m_renderer.SetRenderDrawColor(SDL2::Colors::BLACK));
    // a full refresh is required here to draw the black bg
    Refresh(true);
}

// this will be used for internal splashscreen for example
void Chip8::Screen::Render(PixelGrid grid) const
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

void Chip8::Screen::DrawPoints(SDL_Color color, std::vector<SDL_Rect> rects) const
{
    sdl_assert(m_renderer.SetRenderDrawColor(color));
    sdl_assert(m_renderer.RenderFillRects(std::move(rects)));
}

void Chip8::Screen::DrawSprite(std::vector<Point> pixelsOn)
{
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
    return DrawPoints(SDL2::Colors::WHITE, std::move(rects));
}

void Chip8::Screen::Refresh(bool fullRefresh)
{
    if (fullRefresh)
    {
        // clears screen
        sdl_assert(m_renderer.RenderClear());
        // clears grid cache
        ResetGrid(m_grid);
    }
    // renders screen
    m_renderer.RenderPresent();
}

void Chip8::Screen::ChangeBgColor(SDL_Color color, bool fullRefresh)
{
    sdl_assert(m_renderer.SetRenderDrawColor(color));
    Refresh(fullRefresh);
}

bool Chip8::Screen::Collides(uint8_t x, uint8_t y) const
{
    assert(x >= 0 && x <= base_width);
    assert(y >= 0 && y <= base_height);
    return m_grid[x][y];
}

// TODO Implement the char rendering function

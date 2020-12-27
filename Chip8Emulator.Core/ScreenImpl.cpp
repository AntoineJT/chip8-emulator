#include "include/ScreenImpl.hpp"

#include <sdl_assert.h>

#include "sdl_colors.hpp"

Chip8::ScreenImpl::ScreenImpl(const SDL2::SDL& sdl, const std::uint8_t ratio) noexcept
    : Screen(sdl, ratio)
{
    // set background to black
    sdl_assert(m_renderer.SetRenderDrawColor(SDL2::Colors::BLACK));
    // a full refresh is required here to draw the black bg
    ScreenImpl::Refresh(true);
}

// this will be used for internal splashscreen for example
void Chip8::ScreenImpl::Render(const PixelGrid& grid) const
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

void Chip8::ScreenImpl::ChangeBgColor(const SDL_Color color, const bool fullRefresh) noexcept
{
    sdl_assert(m_renderer.SetRenderDrawColor(color));
    Refresh(fullRefresh);
}

void Chip8::ScreenImpl::Refresh(const bool fullRefresh) noexcept
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

void Chip8::ScreenImpl::DrawPoints(SDL_Color color, const std::vector<SDL_Rect>& rects) const noexcept
{
    sdl_assert(m_renderer.SetRenderDrawColor(color));
    sdl_assert(m_renderer.RenderFillRects(rects));
}

void Chip8::ScreenImpl::DrawSprite(const std::vector<Point>& pixelsOn)
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

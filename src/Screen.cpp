#include "Screen.hpp"

#include <array>
#include <cassert>
#include <cstdint>

#include "sdl.hpp"
#include "sdl_assert.hpp"
#include "sdl_renderer.hpp"
#include "sdl_window.hpp"

SDL2::Window CreateWindow(SDL2::SDL& sdl, uint8_t ratio)
{
    assert(sdl.Running());

    const int width = static_cast<int>(Chip8::base_width) * ratio;
    const int height = static_cast<int>(Chip8::base_height) * ratio;

    return SDL2::Window("Chip8Emu",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height, 0);
}

constexpr SDL_Color black = { 0, 0, 0, 255 };
constexpr SDL_Color white = { 255, 255, 255, 255 };

Chip8::Screen::Screen(SDL2::SDL& sdl, uint8_t ratio)
    : m_ratio(ratio)
    , m_window(CreateWindow(sdl, ratio))
    , m_renderer(SDL2::Renderer(m_window.Data(), -1, SDL_RENDERER_ACCELERATED))
{
    // TODO Faire ça proprement, pour l'instant il s'agit de tests

    for (int i = 5; i > 0; --i)
    {
        // set background to black
        sdl_assert(m_renderer.SetRenderDrawColor(black));
        // a full refresh is required here to draw the black bg
        Refresh(true);

        SDL_Delay(250);

        sdl_assert(m_renderer.SetRenderDrawColor(white));
        Refresh(true);

        SDL_Delay(250);
    }
}

// TODO Maybe rename this
bool Chip8::Screen::DrawPoints(PixelGrid grid) const
{
    std::vector<SDL_Rect> pixelsOff = {};
    std::vector<SDL_Rect> pixelsOn = {};

    for (size_t y = 0; y < base_height; ++y)
    {
        for (size_t x = 0; x < base_width; ++x)
        {
            const bool isOn = grid.at(y).at(x);
            const SDL_Rect rect = {
                static_cast<int>(x) * m_ratio,
                static_cast<int>(y) * m_ratio,
                m_ratio,
                m_ratio
            };

            (isOn ? pixelsOn : pixelsOff).push_back(rect);
        }
    }

    return DrawPoints(black, pixelsOff)
        && DrawPoints(white, pixelsOn);
}

bool Chip8::Screen::DrawPoints(SDL_Color color, std::vector<SDL_Rect> rects) const
{
    sdl_assert(m_renderer.SetRenderDrawColor(color));
    return m_renderer.RenderFillRects(std::move(rects));
}

void Chip8::Screen::Refresh(bool fullRefresh) const
{
    if (fullRefresh)
    {
        // clears screen
        sdl_assert(m_renderer.RenderClear());
    }
    // renders screen
    m_renderer.RenderPresent();
}

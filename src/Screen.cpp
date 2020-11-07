#include "Screen.hpp"

#include <cassert>
#include <cmath>

#include "sdl.hpp"
#include "sdl_assert.hpp"
#include "sdl_renderer.hpp"
#include "sdl_window.hpp"

bool IsMultipleOf(const int base, const int number)
{
    double d = number;
    while (d > base)
    {
        d /= base;
    }
    return std::round(d) == d;
}

Chip8::Screen::Screen(SDL2::SDL& sdl, int width, int height)
{
    assert(sdl.Running());
    assert(IsMultipleOf(Chip8::base_width, width));
    assert(IsMultipleOf(Chip8::base_height, height));
    assert(width / height == base_width / base_height);

    // TODO Faire ça proprement, pour l'instant il s'agit de tests
    SDL2::Window win = SDL2::Window("Chip8Emu",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height, 0);

    SDL2::Renderer renderer = SDL2::Renderer(win.Data(), -1, SDL_RENDERER_ACCELERATED);

    // set background to black
    sdl_assert(renderer.SetRenderDrawColor(0, 0, 0, 255));
    // clears screen
    sdl_assert(renderer.RenderClear());
    // renders screen
    renderer.RenderPresent();

    sdl_assert(renderer.SetRenderDrawColor(255, 255, 255, 255));
    {
        SDL_Rect rect = { 10, 10, 10, 10 };
        sdl_assert(renderer.RenderFillRect(&rect));
    }
    renderer.RenderPresent();

    SDL_Delay(2000);
}

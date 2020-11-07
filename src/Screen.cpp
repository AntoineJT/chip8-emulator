#include "Screen.hpp"

#include <cassert>
#include <cstdint>

#include "sdl.hpp"
#include "sdl_assert.hpp"
#include "sdl_renderer.hpp"
#include "sdl_window.hpp"

Chip8::Screen::Screen(SDL2::SDL& sdl, uint8_t ratio)
{
    // TODO Faire ça proprement, pour l'instant il s'agit de tests
    assert(sdl.Running());

    const int width = base_width * ratio;
    const int height = base_height * ratio;

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

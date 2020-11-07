#include "Screen.hpp"

#include <cassert>

#include "sdl.hpp"
#include "sdl_renderer.hpp"
#include "sdl_window.hpp"

Chip8::Screen::Screen(SDL2::SDL& sdl)
{
    assert(sdl.Running());

    // TODO Faire ça proprement, pour l'instant il s'agit de tests
    SDL2::Window win = SDL2::Window("Chip8Emu",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1000, 1000, 0);

    SDL2::Renderer renderer = SDL2::Renderer(win.Data(), -1, SDL_RENDERER_ACCELERATED);

    // set background to black
    assert(renderer.SetRenderDrawColor(0, 0, 0, 0));
    // clears screen
    assert(renderer.RenderClear());
    // renders screen
    renderer.RenderPresent();

    SDL_Delay(2000);

    
}

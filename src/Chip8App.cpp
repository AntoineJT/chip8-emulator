#include <iostream>
#include <cstdlib>
#include <SDL.h>
#include <sdl_window.hpp>

#include "sdl.hpp"
#include "sdl_renderer.hpp"

#undef main // removes SDL main entry redefinition

int main()
{
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "error initializing SDL: " << SDL_GetError() << std::endl;
    }

    SDL2::SDL sdl = SDL2::SDL();
    sdl.Init(SDL_INIT_EVERYTHING);

    SDL2::Window win = SDL2::Window("GAME",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1000, 1000, 0);

    SDL2::Renderer renderer = SDL2::Renderer(win.Data(), 0, SDL_RENDERER_ACCELERATED);

    SDL_Delay(2000);

    return EXIT_SUCCESS;
}

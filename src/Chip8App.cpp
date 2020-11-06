#include <iostream>
#include <cstdlib>
#include <SDL.h>
#include <SDL_timer.h>
#include <sdl_window.hpp>

#undef main

int main()
{
     // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "error initializing SDL: " << SDL_GetError() << std::endl;
    }
    
    SDL2::Window win = SDL2::Window("GAME",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1000, 1000, 0);

    return EXIT_SUCCESS;
}

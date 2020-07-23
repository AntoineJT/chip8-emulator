#include <iostream>
#include "../../ThirdParty/SDL2/include/SDL.h"

#undef main

int main()
{
    // retutns zero on success else non-zero 
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "error initializing SDL: " << SDL_GetError() << std::endl;
    }
    const SDL_Window* win = SDL_CreateWindow("GAME",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1000, 1000, 0);
    while (win != nullptr);

    return 0;
}

#include <cassert>
#include <iostream>
#include <cstdlib>
#include <SDL.h>
#include <sdl_window.hpp>


#include "Screen.hpp"
#include "sdl.hpp"
#include "sdl_renderer.hpp"

#undef main // removes SDL main entry redefinition

int main()
{
    SDL2::SDL sdl = SDL2::SDL();
    // should not be ALREADY_RUNNING, at least for now
    assert(sdl.Init(SDL_INIT_VIDEO) == SDL2::SDL::INIT_SUCCESS);

    Chip8::Screen screen = Chip8::Screen(sdl);

    return EXIT_SUCCESS;
}

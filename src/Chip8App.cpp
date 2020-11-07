#include <cassert>
#include <iostream>
#include <cstdlib>
#include <SDL.h>
#include <sdl_window.hpp>

#include "Screen.hpp"
#include "sdl.hpp"

#undef main // removes SDL main entry redefinition

int main()
{
    auto sdl = SDL2::SDL();
    // should not be ALREADY_RUNNING, at least for now
    assert(sdl.Init(SDL_INIT_VIDEO) == SDL2::SDL::INIT_SUCCESS);

    auto screen = Chip8::Screen(sdl, 256, 128);
    
    return EXIT_SUCCESS;
}

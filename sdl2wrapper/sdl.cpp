#include "includes/sdl.hpp"

#include <cassert>

SDL2::SDL::~SDL()
{
    assert(m_isRunning);
    m_isRunning = false;
    SDL_Quit();
}

int SDL2::SDL::Init(Uint32 flags)
{
    m_isRunning = true;
    return SDL_Init(flags);
}

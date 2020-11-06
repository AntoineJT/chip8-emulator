#include "includes/sdl.hpp"

#include <cassert>

SDL2::SDL::~SDL()
{
    if (m_isRunning)
        return;
    Quit();
}

void SDL2::SDL::Quit()
{
    assert(m_isRunning);
    m_isRunning = false;
    SDL_Quit();
}

int SDL2::SDL::Init(Uint32 flags)
{
    if (m_isRunning)
        return ALREADY_RUNNING;

    m_isRunning = true;
    int retval = SDL_Init(flags);

    if (retval < INIT_SUCCESS)
        return INIT_FAILURE;
    return INIT_SUCCESS;
}

bool SDL2::SDL::Running() const
{
    return m_isRunning;
}

#include "include/sdl.hpp"

#include <cassert>

// Set mainHandled to true if you remove
// the SDL_main entry point by defining
// SDL_MAIN_HANDLED before to include SDL
SDL2::SDL::SDL(const bool mainHandled) noexcept
{
    if (mainHandled)
    {
        SDL_SetMainReady();
    }
}

SDL2::SDL::~SDL() noexcept
{
    if (!m_isRunning)
        return;
    Quit();
}

void SDL2::SDL::Quit() noexcept
{
    assert(m_isRunning);
    m_isRunning = false;
    SDL_Quit();
}

int SDL2::SDL::Init(const Uint32 flags) noexcept
{
    if (m_isRunning)
        return ALREADY_RUNNING;

    m_isRunning = true;
    const int ret = SDL_Init(flags);

    if (ret < INIT_SUCCESS)
        return INIT_FAILURE;
    return INIT_SUCCESS;
}

bool SDL2::SDL::Running() const noexcept
{
    return m_isRunning;
}
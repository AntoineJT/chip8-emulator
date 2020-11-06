#include "includes/sdl_renderer.hpp"

#include <cassert>
#include <SDL.h>

SDL2::Renderer::Renderer(SDL_Window* window, int index, Uint32 flags)
{
    m_pRenderer = SDL_CreateRenderer(window, index, flags);
    assert(m_pRenderer != nullptr);
}

SDL2::Renderer::~Renderer()
{
    SDL_DestroyRenderer(m_pRenderer);
}

SDL_Renderer* SDL2::Renderer::Data()
{
    return m_pRenderer;
}

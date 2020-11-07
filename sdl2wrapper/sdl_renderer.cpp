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

SDL_Renderer* SDL2::Renderer::Data() const
{
    return m_pRenderer;
}

bool SDL2::Renderer::SetRenderDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const
{
    return SDL_SetRenderDrawColor(m_pRenderer, r, g, b, a) == 0;
}

bool SDL2::Renderer::RenderClear() const
{
    return SDL_RenderClear(m_pRenderer) == 0;
}

void SDL2::Renderer::RenderPresent() const
{
    SDL_RenderPresent(m_pRenderer);
}

bool SDL2::Renderer::RenderFillRect(const SDL_Rect* rect) const
{
    return SDL_RenderFillRect(m_pRenderer, rect) == 0;
}

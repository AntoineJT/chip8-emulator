#include "includes/sdl_renderer.hpp"

#include <cassert>
#include <memory>
#include <SDL.h>
#include <vector>

#include "includes/sdl_window.hpp"

constexpr int SUCCESS = 0;

// do not replace this raw pointer with a unique_ptr
// this ctor exists to interop with C functions
SDL2::Renderer::Renderer(SDL_Window* window, int index, Uint32 flags)
{
    m_pRenderer = SDL_CreateRenderer(window, index, flags);
    assert(m_pRenderer != nullptr);
}

SDL2::Renderer::Renderer(SDL_Renderer* renderer)
    : m_pRenderer(renderer)
{
    assert(renderer != nullptr);
}

SDL2::Renderer::Renderer(Window& window, int index, Uint32 flags)
    : Renderer(window.Data(), index, flags)
{}

SDL2::Renderer::~Renderer()
{
    SDL_DestroyRenderer(m_pRenderer);
}

SDL_Renderer* SDL2::Renderer::Data() const
{
    return m_pRenderer;
}

bool SDL2::Renderer::SetRenderDrawColor(const SDL_Color color) const
{
    return SDL_SetRenderDrawColor(m_pRenderer, color.r, color.g, color.b, color.a)
        == SUCCESS;
}

bool SDL2::Renderer::RenderClear() const
{
    return SDL_RenderClear(m_pRenderer) == SUCCESS;
}

void SDL2::Renderer::RenderPresent() const
{
    SDL_RenderPresent(m_pRenderer);
}

bool SDL2::Renderer::RenderFillRect(std::unique_ptr<SDL_Rect> rect) const
{
    return SDL_RenderFillRect(m_pRenderer, rect.get()) == SUCCESS;
}

bool SDL2::Renderer::RenderFillRects(std::vector<SDL_Rect> rect) const
{
    return SDL_RenderFillRects(m_pRenderer, rect.data(), rect.size())
        == SUCCESS;
}

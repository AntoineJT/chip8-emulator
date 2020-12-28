#include "sdl_renderer.hpp"

#include <cassert>
#include <climits>
#include <memory>
#include <SDL.h>
#include <vector>

#include "sdl_window.hpp"

constexpr int SUCCESS = 0;

// do not replace this raw pointer with a unique_ptr
// this ctor exists to interop with C functions
SDL2::Renderer::Renderer(SDL_Window* window, const int index, const Uint32 flags) noexcept
{
    m_pRenderer = SDL_CreateRenderer(window, index, flags);
    assert(m_pRenderer != nullptr);
}

SDL2::Renderer::Renderer(SDL_Renderer* renderer) noexcept
    : m_pRenderer(renderer)
{
    assert(renderer != nullptr);
}

SDL2::Renderer::Renderer(const Window& window, const int index, const Uint32 flags) noexcept
    : Renderer(window.Data(), index, flags)
{}

SDL2::Renderer::~Renderer() noexcept
{
    SDL_DestroyRenderer(m_pRenderer);
}

SDL_Renderer* SDL2::Renderer::Data() const noexcept
{
    return m_pRenderer;
}

bool SDL2::Renderer::SetRenderDrawColor(const SDL_Color color) const noexcept
{
    return SDL_SetRenderDrawColor(m_pRenderer, color.r, color.g, color.b, color.a)
        == SUCCESS;
}

bool SDL2::Renderer::RenderClear() const noexcept
{
    return SDL_RenderClear(m_pRenderer) == SUCCESS;
}

void SDL2::Renderer::RenderPresent() const noexcept
{
    SDL_RenderPresent(m_pRenderer);
}

bool SDL2::Renderer::RenderFillRect(const std::unique_ptr<SDL_Rect> rect) const noexcept
{
    return SDL_RenderFillRect(m_pRenderer, rect.get()) == SUCCESS;
}

bool SDL2::Renderer::RenderFillRects(const std::vector<SDL_Rect>& rect) const noexcept
{
    const auto size = rect.size();
    assert(size <= INT_MAX);
    return SDL_RenderFillRects(m_pRenderer, rect.data(), static_cast<int>(size))
        == SUCCESS;
}

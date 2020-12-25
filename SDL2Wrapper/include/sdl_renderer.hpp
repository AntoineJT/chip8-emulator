#pragma once
#include <memory>
#include <SDL.h>
#include <vector>

#include "sdl_window.hpp"

namespace SDL2
{
    class Renderer
    {
        SDL_Renderer* m_pRenderer;

    public:
        Renderer(SDL_Window* window, int index, Uint32 flags) noexcept;
        Renderer(SDL_Renderer* renderer) noexcept;
        Renderer(const Window& window, int index, Uint32 flags) noexcept;
        ~Renderer() noexcept;
        Renderer(Renderer&&) = default;
        Renderer& operator=(Renderer&&) = default;

        SDL_Renderer* Data() const noexcept;
        bool SetRenderDrawColor(SDL_Color color) const noexcept;
        bool RenderClear() const noexcept;
        void RenderPresent() const noexcept;
        bool RenderFillRect(std::unique_ptr<SDL_Rect> rect) const noexcept;
        bool RenderFillRects(const std::vector<SDL_Rect>& rect) const noexcept;
    };
};

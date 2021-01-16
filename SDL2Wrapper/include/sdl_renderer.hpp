#pragma once
#include <memory>
#include <SDL.h>
#include <vector>

#include "sdl_colors.hpp"
#include "sdl_window.hpp"

namespace SDL2
{
    class Renderer
    {
        SDL_Renderer* m_pRenderer;
        SDL_Color m_drawColor = Colors::BLACK;

    public:
        Renderer(SDL_Window* window, int index, Uint32 flags) noexcept;
        Renderer(SDL_Renderer* renderer) noexcept;
        Renderer(const Window& window, int index, Uint32 flags) noexcept;
        ~Renderer() noexcept;
        Renderer(Renderer&&) = default;
        Renderer& operator=(Renderer&&) = default;

        SDL_Renderer* Data() const noexcept;
        void SetRenderDrawColor(SDL_Color color) noexcept;
        void RenderClear() const noexcept;
        SDL_Color RenderDrawColor() const noexcept;
        void RenderPresent() const noexcept;
        void RenderFillRect(std::unique_ptr<SDL_Rect> rect) const noexcept;
        void RenderFillRects(const std::vector<SDL_Rect>& rect) const noexcept;
    };
};

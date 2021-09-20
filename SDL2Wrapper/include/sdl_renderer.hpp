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
        Renderer(SDL_Window* window, int index, Uint32 flags);
        Renderer(SDL_Renderer* renderer);
        Renderer(const Window& window, int index, Uint32 flags);
        ~Renderer();
        Renderer(Renderer&&) = default;
        Renderer& operator=(Renderer&&) = default;

        SDL_Renderer* Data() const;
        void SetDrawColor(SDL_Color color);
        void RenderClear() const;
        SDL_Color DrawColor() const;
        void RenderPresent() const;
        void FillRect(const SDL_Rect* rect) const;
        void FillRects(const std::vector<SDL_Rect>& rect) const;
    };
};

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
        Renderer(SDL_Window* window, int index, Uint32 flags);
        Renderer(SDL_Renderer* renderer);
        Renderer(Window& window, int index, Uint32 flags);
        ~Renderer();
        SDL_Renderer* Data() const;
        bool SetRenderDrawColor(SDL_Color color) const;
        bool RenderClear() const;
        void RenderPresent() const;
        bool RenderFillRect(std::unique_ptr<SDL_Rect> rect) const;
        bool RenderFillRects(std::vector<SDL_Rect> rect) const;
    };
};

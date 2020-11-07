#pragma once
#include <SDL.h>

namespace SDL2
{
    class Renderer
    {
        SDL_Renderer* m_pRenderer;

    public:
        Renderer(SDL_Window* window, int index, Uint32 flags);
        ~Renderer();
        SDL_Renderer* Data() const;
        bool SetRenderDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;
        bool RenderClear() const;
        void RenderPresent() const;
        bool RenderFillRect(const SDL_Rect* rect) const;
    };
};

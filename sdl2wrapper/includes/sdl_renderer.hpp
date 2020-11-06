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
        SDL_Renderer* Data();
    };
};

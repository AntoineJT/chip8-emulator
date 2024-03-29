#pragma once
#include "SDL.h"

namespace SDL2
{
    struct Window 
    {
        private:
            SDL_Window* m_pWindow;
        
        public:
            Window(const char* title, int x, int y, int w, int h, Uint32 flags);
            ~Window();
            Window(Window&&) = default;
            Window& operator=(Window&&) = default;

            SDL_Window* Data() const;
    };
};

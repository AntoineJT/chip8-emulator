#include <SDL.h>
#include "includes/sdl_window.hpp"

SDL2::Window::Window(const char* title, int x, int y, int w, int h, Uint32 flags)
{
    m_pWindow = SDL_CreateWindow(title, x, y, w, h, flags);
}

SDL2::Window::~Window()
{
    SDL_DestroyWindow(m_pWindow);
}

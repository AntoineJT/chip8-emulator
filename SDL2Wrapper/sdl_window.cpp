#include "sdl_window.hpp"
#include <SDL.h>

#include <cassert>

SDL2::Window::Window(const char* title, const int x, const int y, 
    const int w, const int h, const Uint32 flags)
{
    m_pWindow = SDL_CreateWindow(title, x, y, w, h, flags);
    assert(m_pWindow != nullptr);
}

SDL2::Window::~Window()
{
    SDL_DestroyWindow(m_pWindow);
}

SDL_Window* SDL2::Window::Data() const
{
    return m_pWindow;
}

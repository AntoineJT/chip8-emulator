#include "include/sdl_window.hpp"
#include <SDL.h>

#include <cassert>

SDL2::Window::Window(const char* title, int x, int y, int w, int h, Uint32 flags)
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

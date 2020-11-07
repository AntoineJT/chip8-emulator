#pragma once
#include <cassert>
#include <iostream>
#include <SDL.h>

#define sdl_assert(expr) \
    if (!expr) \
    { \
        std::cout << SDL_GetError() << std::endl; \
        assert(expr); \
    }

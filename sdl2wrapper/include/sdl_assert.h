#pragma once
#include <cassert>
#include <iostream>
#include <SDL.h>

// NOTE: evaluates 2 times expr if expr is false first!
#define sdl_assert(expr) \
    if (!expr) \
    { \
        std::cout << SDL_GetError() << std::endl; \
        assert(expr); \
    }

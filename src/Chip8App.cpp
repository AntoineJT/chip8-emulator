#include <cassert>
#include <iostream>
#include <cstdlib>
#include <SDL.h>

#include "Screen.hpp"
#include "sdl.hpp"
#include "sdl_assert.hpp"
#include "sdl_colors.hpp"

#undef main // removes SDL main entry redefinition

int main()
{
    SDL2::SDL sdl;
    // should not be ALREADY_RUNNING, at least for now
    assert(sdl.Init(SDL_INIT_VIDEO) == SDL2::SDL::INIT_SUCCESS);

    Chip8::Screen screen(sdl, 16);

    Chip8::Screen::PixelGrid grid = {};
    for (std::size_t y = 0; y < Chip8::base_height; ++y)
    {
        grid.at(y) = {};
        for (std::size_t x = 0; x < Chip8::base_width; ++x)
        {
            grid[y][x] = x % (y + 1) == 0;
        }
    }
    assert(screen.Render(grid));
    screen.Refresh(false);

    SDL_Delay(3000);

    // Blinking screen test
    for (int i = 5; i > 0; --i)
    {
        screen.ChangeBgColor(SDL2::Colors::BLACK, true);
        SDL_Delay(250);
        screen.ChangeBgColor(SDL2::Colors::WHITE, true);
        SDL_Delay(250);
    }
    
    return EXIT_SUCCESS;
}

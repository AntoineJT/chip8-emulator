#include <cassert>
#include <cstdlib>
#include <iostream>

#define SDL_MAIN_HANDLED

#include "LoadFileFunc.hpp"
#include "Machine.hpp"
#include "PrintUsageFunc.hpp"
#include "Screen.hpp"
#include "sdl.hpp"
#include "sdl_assert.h"

#include <SDL.h>
#include <unordered_map>

int main(int argc, char* argv[])
{
    std::string filename;

    if (argc == 1) {
        std::cerr << "Not enough arguments." << std::endl;
        Chip8::Utils::PrintUsage(argv[0]);
        return EXIT_FAILURE;
    }
    if (argc == 2) {
        filename = argv[1];
    }
    else {
        std::cerr << "Too much arguments." << std::endl;
        Chip8::Utils::PrintUsage(argv[0]);
        return EXIT_FAILURE;
    }

    auto sdl = std::make_shared<SDL2::SDL>(true);
    // should not be ALREADY_RUNNING, at least for now
    sdl_assert((*sdl.get()).Init(SDL_INIT_VIDEO) == SDL2::SDL::INIT_SUCCESS);

    std::vector<char> content;
    if (!Chip8::Utils::LoadFile(content, filename))
    {
        return EXIT_FAILURE;
    }

    Chip8::Screen screen(sdl, 16);
    sdl.reset();
    Chip8::Memory memory;
    memory.LoadProgram(content);
    Chip8::Keyboard keyboard;
    Chip8::Machine machine(screen, memory, keyboard);

    std::cout << "Press CTRL^C to quit" << std::endl;

    constexpr auto refreshRate = static_cast<Uint32>(1000 / 60);
    while(true)
    {
        machine.HandleEvents();
        machine.ExecuteNextInstruction();
        SDL_Delay(refreshRate);
    }

    /*
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
    */
}

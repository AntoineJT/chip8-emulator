#include <cassert>
#include <cstdlib>
#include <iostream>
#include <unordered_map>

#include "Machine.hpp"
#include "PrintUsageFunc.hpp"
#include "Screen.hpp"
#include "sdl.hpp"
#include "sdl_assert.h"

#include <SDL.h>

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

    auto sdlPtr = std::make_shared<SDL2::SDL>(true);
    // should not be ALREADY_RUNNING, at least for now
    sdl_assert(sdlPtr->Init(SDL_INIT_VIDEO) == SDL2::SDL::INIT_SUCCESS);

    auto screenPtr = std::make_shared<Chip8::Screen>(sdlPtr, 16);
    sdlPtr.reset();

    Chip8::Machine machine(screenPtr, filename);
    screenPtr.reset();

    std::cout << "Press CTRL^C to quit" << std::endl;

    constexpr auto refreshRate = static_cast<Uint32>(1000 / 60);
    while(true)
    {
        machine.HandleEvents();
        machine.ExecuteNextInstruction();
        SDL_Delay(refreshRate);
    }
}

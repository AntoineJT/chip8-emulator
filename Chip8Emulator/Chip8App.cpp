#include <cassert>
#include <cstdlib>
#include <iostream>
#include <unordered_map>

#include "Delay.hpp"
#include "Machine.hpp"
#include "Screen.hpp"
#include "sdl.hpp"
#include "sdl_assert.h"

#include <SDL.h>

static void PrintUsage(const char* filename)
{
    std::cerr << "Usage: " << filename << " inputfile" << std::endl;
}

int main(int argc, char* argv[])
{
    std::string filename;

    if (argc == 1) {
        std::cerr << "Not enough arguments." << std::endl;
        PrintUsage(argv[0]);
        return EXIT_FAILURE;
    }
    if (argc == 2) {
        filename = argv[1];
    }
    else {
        std::cerr << "Too much arguments." << std::endl;
        PrintUsage(argv[0]);
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

    // see: https://www.reddit.com/r/EmuDev/comments/a6m2z1/question_about_chip8_op_execution_per_tick/
    constexpr int nsBetweenFrame = Chip8::Utils::FpsDelayNs(400);
    while(true)
    {
        machine.HandleEvents();
        machine.ExecuteNextInstruction();
        Chip8::Utils::WaitNs(nsBetweenFrame);
    }
}

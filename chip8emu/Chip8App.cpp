#include <cassert>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <SDL.h>

#include "Machine.hpp"
#include "Screen.hpp"
#include "sdl.hpp"
#include "sdl_assert.hpp"

#undef main // removes SDL main entry redefinition

void PrintUsage(std::string const& filename)
{
    std::cout << "Usage: " << filename << " [inputfile]" << std::endl;
}

int main(int argc, char* argv[])
{
    std::string filename;

    if (argc == 1) {
        std::cout << "Not enough arguments." << std::endl;
        PrintUsage(argv[0]);
        return EXIT_FAILURE;
    }
    if (argc == 2) {
        filename = argv[1];
    }
    else {
        std::cout << "Too much arguments." << std::endl;
        PrintUsage(argv[0]);
        return EXIT_FAILURE;
    }

    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if (!file.is_open()) {
        std::cout << "Failed to open '" << filename << "'." << std::endl;
        return EXIT_FAILURE;
    }

    const auto end = file.tellg();
    file.seekg(0, std::ios::beg);
    const auto size = std::size_t(end - file.tellg());

    if (size == 0) {
        std::cout << "The file '" << filename << "' was empty." << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<char> content(size);
    if (!file.read(content.data(), content.size())) {
        throw std::runtime_error(filename + ": " + std::strerror(errno));
    }
    file.close();

    SDL2::SDL sdl;
    // should not be ALREADY_RUNNING, at least for now
    assert(sdl.Init(SDL_INIT_VIDEO) == SDL2::SDL::INIT_SUCCESS);

    Chip8::Screen screen(sdl, 16);
    Chip8::Memory memory;
    memory.LoadProgram(content);
    Chip8::Machine machine(std::move(screen), memory);

    while(true) // 
    {
        machine.ExecuteNextInstruction();
        SDL_Delay(1 / 60 * 1000);
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
    
    return EXIT_SUCCESS;
}

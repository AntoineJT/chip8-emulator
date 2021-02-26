#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>

#define SDL_MAIN_HANDLED

#include "CurrentDateFunc.hpp"
#include "DumpMemoryFunc.hpp"
#include "LoadFileFunc.hpp"
#include "Machine.hpp"
#include "Memory.hpp"
#include "Opcode2AsmFunc.hpp"
#include "Screen.hpp"
#include "sdl.hpp"

#include <SDL.h>
#include <tclap/CmdLine.h>

void PrintUsage(const char* filename) noexcept
{
    std::cerr << "Usage: " << filename << " inputfile [delay]" << std::endl
        << std::endl
        << "Parameters" << std::endl
        << "inputfile: Input file" << std::endl
        << "delay: Time in milliseconds between instructions" << std::endl;
    // TODO make/use a real argument parser in order to make that
/*
        << std::endl
        << "Flags" << std::endl
        << "--no-heap: Don't dump heap memory" << std::endl;
*/
}

int main(int argc, char* argv[])
{
    std::string filename;
    int delay = 500;

    switch(argc)
    {
    case 1:
        std::cerr << "Not enough arguments." << std::endl;
        PrintUsage(argv[0]);
        return EXIT_FAILURE;
    case 2:
        filename = argv[1];
        break;
    case 3:
        filename = argv[1];
        delay = std::atoi(argv[2]);
        break;
    default:
        std::cerr << "Too much arguments." << std::endl;
        PrintUsage(argv[0]);
        return EXIT_FAILURE;
    }

    const std::string ofname = filename + "_" + CurrentDate() + "_dump.txt";
    std::ofstream output(ofname);
    if (!output.is_open())
    {
        std::cerr << "Can't create file '" << ofname << "'!" << std::endl;
        return EXIT_FAILURE;
    }

    // sets up the emulator to be able to dump memory
    SDL2::SDL sdl(true);
    assert(sdl.Init(SDL_INIT_VIDEO) == SDL2::SDL::INIT_SUCCESS);
    Chip8::Screen screen(sdl, 4);
    Chip8::Memory mem;
    std::vector<char> content;
    if (!Chip8::Utils::LoadFile(content, filename))
    {
        return EXIT_FAILURE;
    }
    mem.LoadProgram(content);
    Chip8::Machine machine(screen, mem);

    while(true)
    {
        const std::uint16_t opcode = mem.NextInstruction();

        machine.Execute(opcode);
        output << Chip8::Disasm::Opcode2Asm(opcode) << '\n'
            << Chip8::Dump::DumpMemory(mem) << '\n';

        SDL_Delay(delay);
    }
}

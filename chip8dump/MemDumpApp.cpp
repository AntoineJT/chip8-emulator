#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>

#include "LoadFileFunc.hpp"
#include "Machine.hpp"
#include "Memory.hpp"
#include "Opcode2AsmFunc.hpp"
#include "Screen.hpp"
#include "sdl.hpp"

#include <SDL.h>

#include "CurrentDateFunc.hpp"
#include "DumpMemoryFunc.hpp"
#include "PrintUsageFunc.hpp"

#undef main

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

    std::ofstream output(filename + "_" + CurrentDate() + "_dump.txt");
    assert(output.is_open());

    // sets up the emulator to be able to dump memory
    SDL2::SDL sdl;
    assert(sdl.Init(SDL_INIT_VIDEO) == SDL2::SDL::INIT_SUCCESS);
    Chip8::Screen screen(sdl, 1);
    Chip8::Memory mem;
    mem.LoadProgram(Chip8::Utils::LoadFile(filename));
    Chip8::Machine machine(screen, mem);

    while(true)
    {
        const std::uint16_t opcode = mem.NextInstruction();
        const std::string instruction = Chip8::Disasm::Opcode2Asm(opcode);

        machine.Execute(opcode);
        output << instruction << '\n'
            << Chip8::Dump::DumpMemory(mem) << '\n';
    }
}

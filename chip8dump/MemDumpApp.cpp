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

    const std::string ofname = filename + "_" + CurrentDate() + "_dump.txt";
    std::ofstream output(ofname);
    if (!output.is_open())
    {
        std::cerr << "Can't create file '" << ofname << "'!" << std::endl;
        return EXIT_FAILURE;
    }

    // sets up the emulator to be able to dump memory
    SDL2::SDL sdl;
    assert(sdl.Init(SDL_INIT_VIDEO) == SDL2::SDL::INIT_SUCCESS);
    Chip8::Screen screen(sdl, 1);
    Chip8::Memory mem;
    std::vector<char> content;
    if (!Chip8::Utils::LoadFile(content, filename))
    {
        return EXIT_FAILURE;
    }
    mem.LoadProgram(content);
    Chip8::Machine machine(screen, mem);

    std::string lastHeapDump;
    while(true)
    {
        const std::uint16_t opcode = mem.NextInstruction();

        machine.Execute(opcode);
        output << Chip8::Disasm::Opcode2Asm(opcode) << '\n'
            << Chip8::Dump::DumpMemoryV2(mem) << '\n';

        // TODO Fix it
        /*
        std::string heapDump = Chip8::Dump::DumpHeap(mem);

        output << Chip8::Disasm::Opcode2Asm(opcode) << '\n'
            << Chip8::Dump::DumpMemoryV2(mem, lastHeapDump, heapDump) << '\n';

        lastHeapDump = std::move(heapDump);
        */
    }
}

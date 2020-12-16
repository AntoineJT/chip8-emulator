#include <algorithm>
#include <cassert>
#include <ctime>
#include <fstream>
#include <iostream>

#include "LoadFileFunc.hpp"
#include "Machine.hpp"
#include "Memory.hpp"
#include "Opcode2AsmFunc.hpp"
#include "OpcodeValueFunc.hpp"
#include "Screen.hpp"
#include "sdl.hpp"

#undef main

void PrintUsage(std::string const& filename)
{
    std::cout << "Usage: " << filename << " [inputfile]" << std::endl;
}

std::string CurrentDate()
{
    const std::time_t time = std::time(nullptr);
    std::string date(std::asctime(std::localtime(&time)));

    std::replace(date.begin(), date.end(), ' ', '_');
    return date;
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

    const auto content = Chip8::Utils::LoadFile(filename);
    const std::size_t size = content.size();

    std::ofstream output("_dump.txt");
    assert(output.is_open());

    // sets up the emulator to be able to dump memory
    SDL2::SDL sdl;
    assert(sdl.Init(SDL_INIT_VIDEO) == SDL2::SDL::INIT_SUCCESS);
    Chip8::Screen screen(sdl, 1);
    Chip8::Memory mem;
    Chip8::Machine machine(screen, mem);

    // this is shit, I don't want to disassemble this but to debug it
    // TODO Get next instruction using PC, not iterating on file
    for (std::size_t i = 0; i < size; i += 2)
    {
        const std::uint16_t opcode = Chip8::Utils::OpcodeValue(content[i], content[i + 1]);
        const std::string instruction = Chip8::Disasm::Opcode2Asm(opcode);

        machine.Execute(opcode);
        // TODO Dump memory too
        output << instruction << '\n'
               << std::flush;
    }

    return EXIT_SUCCESS;
}

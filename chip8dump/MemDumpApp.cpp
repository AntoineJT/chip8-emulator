#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

#include "Hex.hpp"
#include "LoadFileFunc.hpp"
#include "Machine.hpp"
#include "Memory.hpp"
#include "Opcode2AsmFunc.hpp"
#include "Screen.hpp"
#include "sdl.hpp"

#include <SDL.h>

#include "CurrentDateFunc.hpp"
#include "PrintUsageFunc.hpp"

#undef main

template<typename T>
std::string ToHex(const T number) noexcept
{
    static_assert(std::is_arithmetic<T>::value, "ToHex only accepts numeric types!");

    std::ostringstream stream;
    stream << "0x" << std::hex << std::to_string(number);
    return stream.str();
}

std::string DumpMemory(const Chip8::Memory& mem) noexcept
{
    std::ostringstream stream;

    constexpr auto U16ToHex = ToHex<std::uint16_t>;
    constexpr auto U8ToHex = ToHex<std::uint8_t>;

    // TODO Remove either U8ToHex or Chip8::Hex::ByteHexValue

    // V0 - VF registers
    for (std::uint8_t i = 0x0; i <= 0xF; ++i)
    {
        stream << 'V' << Chip8::Hex::Uint4HexValue(i) << ": "
               << U8ToHex(mem.VX[i]) << '\n';
    }

    // I register
    stream << "I: " << U16ToHex(mem.I) << '\n';

    // stack pointer
    stream << "SP: " << U8ToHex(mem.sp) << '\n';

    // stack content
    for (std::uint8_t i = 0x0; i <= 0xF; ++i)
    {
        stream << 'S' << Chip8::Hex::Uint4HexValue(i) << ": "
               << U16ToHex(mem.stack[i]) << '\n';
    }

    // delay timer
    stream << "DT: " << U8ToHex(mem.DT) << '\n';

    // sound timer
    stream << "ST: " << U8ToHex(mem.ST) << '\n';

    // program counter
    stream << "PC: " << U16ToHex(mem.pc) << '\n';

    // memory
    stream << "Memory: " << '\n';
    constexpr std::size_t turns = 64;
    static_assert(turns * turns == Chip8::Memory::ram_size);
    for (std::size_t i = 0; i < turns; ++i)
    {
        for (std::size_t j = 0; j < turns; ++j)
        {
            stream << mem.memory[i * turns + j];
        }
        stream << '\n';
    }

    return stream.str();
}

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
            << DumpMemory(mem) << '\n';
    }
}

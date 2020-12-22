#include "DumpMemoryFunc.hpp"

#include <string>
#include <sstream>

#include "Hex.hpp"
#include "Memory.hpp"

std::string Chip8::Dump::DumpMemory(const Memory& mem)
{
    std::ostringstream stream;

    // V0 - VF registers
    for (std::uint8_t i = 0x0; i <= 0xF; ++i)
    {
        stream << 'V' << Hex::Uint4HexValue(i) << ": "
            << Hex::U8ToHex(mem.VX[i]) << '\n';
    }

    // I register
    stream << "I: " << Hex::U16ToHex(mem.I) << '\n';

    // stack pointer
    stream << "SP: " << Hex::U8ToHex(mem.sp) << '\n';

    // stack content
    for (std::uint8_t i = 0x0; i <= 0xF; ++i)
    {
        stream << 'S' << Hex::Uint4HexValue(i) << ": "
            << Hex::U16ToHex(mem.stack[i]) << '\n';
    }

    // delay timer
    stream << "DT: " << Hex::U8ToHex(mem.DT) << '\n';

    // sound timer
    stream << "ST: " << Hex::U8ToHex(mem.ST) << '\n';

    // program counter
    stream << "PC: " << Hex::U16ToHex(mem.pc) << '\n';

    // memory
    stream << "Memory: " << '\n';
    constexpr std::size_t turns = 64;
    static_assert(turns * turns == Memory::ram_size);
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

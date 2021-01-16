#include "DumpMemoryFunc.hpp"

#include <string>
#include <sstream>

#include "Hex.hpp"
#include "Memory.hpp"

constexpr std::size_t turns = 64;

std::ostringstream DumpMemoryWithoutHeap(const Chip8::Memory& mem)
{
    std::ostringstream stream;

    // V0 - VF registers
    for (std::uint8_t i = 0x0; i <= 0xF; ++i)
    {
        stream << 'V' << Chip8::Hex::Uint4HexValue(i) << ": "
            << Chip8::Hex::U8ToHex(mem.VX[i]) << '\n';
    }

    // I register
    stream << "I: " << Chip8::Hex::U16ToHex(mem.I) << '\n';

    // stack pointer
    stream << "SP: " << Chip8::Hex::U8ToHex(mem.sp) << '\n';

    // stack content
    for (std::uint8_t i = 0x0; i <= 0xF; ++i)
    {
        stream << 'S' << Chip8::Hex::Uint4HexValue(i) << ": "
            << Chip8::Hex::U16ToHex(mem.stack[i]) << '\n';
    }

    // delay timer
    stream << "DT: " << Chip8::Hex::U8ToHex(mem.DT) << '\n';

    // sound timer
    stream << "ST: " << Chip8::Hex::U8ToHex(mem.ST) << '\n';

    // program counter
    stream << "PC: " << Chip8::Hex::U16ToHex(mem.pc) << '\n';

    return stream;
}

void Chip8::Dump::DumpHeap(std::ostringstream& stream, const Memory& mem)
{
    static_assert(turns * turns == Memory::ram_size);
    for (std::size_t i = 0; i < turns; ++i)
    {
        for (std::size_t j = 0; j < turns; ++j)
        {
            stream << mem.memory[i * turns + j];
        }
        stream << '\n';
    }
}

std::string Chip8::Dump::DumpHeap(const Memory& mem)
{
    std::ostringstream stream;
    DumpHeap(stream, mem);
    return stream.str();
}

std::string Chip8::Dump::DumpMemory(const Memory& mem)
{
    auto stream = DumpMemoryWithoutHeap(mem);
    stream << "Memory: " << '\n';
    DumpHeap(stream, mem);
    return stream.str();
}

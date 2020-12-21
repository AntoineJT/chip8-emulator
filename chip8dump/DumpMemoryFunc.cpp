#include "DumpMemoryFunc.hpp"

#include <string>
#include <sstream>

#include "Hex.hpp"
#include "Memory.hpp"

std::string Chip8::Dump::DumpMemory(const Chip8::Memory& mem) noexcept
{
    // TODO Remove either U8ToHex or Chip8::Hex::ByteHexValue
    constexpr auto U16ToHex = Chip8::Hex::ToHex<std::uint16_t>;
    constexpr auto U8ToHex = Chip8::Hex::ToHex<std::uint8_t>;

    std::ostringstream stream;

    // V0 - VF registers
    for (std::uint8_t i = 0x0; i <= 0xF; ++i)
    {
        stream << 'V' << Hex::Uint4HexValue(i) << ": "
            << U8ToHex(mem.VX[i]) << '\n';
    }

    // I register
    stream << "I: " << U16ToHex(mem.I) << '\n';

    // stack pointer
    stream << "SP: " << U8ToHex(mem.sp) << '\n';

    // stack content
    for (std::uint8_t i = 0x0; i <= 0xF; ++i)
    {
        stream << 'S' << Hex::Uint4HexValue(i) << ": "
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

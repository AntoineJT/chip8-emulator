#include "include/Hex.hpp"

#include <cassert>
#include <string>

char Chip8::Hex::Uint4HexValue(const std::uint8_t hexInt) noexcept
{
    assert(hexInt <= 0xF);
    switch (hexInt)
    {
    case 0xA:
        return 'A';
    case 0xB:
        return 'B';
    case 0xC:
        return 'C';
    case 0xD:
        return 'D';
    case 0xE:
        return 'E';
    case 0xF:
        return 'F';
    default:
        return static_cast<char>(hexInt + 0x30); // 0x30 is the ASCII offset with numbers
    }
}

std::string Chip8::Hex::AddrHexValue(const std::uint16_t nnn)
{
    assert(nnn <= 0xFFF);
    return U16ToHex(nnn);
}

#include "Hex.hpp"

#include <cassert>
#include <string>

char Chip8::Hex::Uint4HexValue(std::uint8_t hexInt)
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

std::string Chip8::Hex::ByteHexValue(std::uint8_t byte)
{
    const std::uint8_t upper = (byte & 0xF0) >> 4;
    const std::uint8_t lower = byte & 0x0F;

    std::string ret;
    ret.push_back(Uint4HexValue(upper));
    ret.push_back(Uint4HexValue(lower));

    return ret;
}

std::string Chip8::Hex::AddrHexValue(std::uint16_t nnn)
{
    assert(nnn <= 0xFFF);
    const std::uint8_t upper = (nnn & 0xF00) >> 8;
    const std::uint8_t lower = nnn & 0x0FF;

    return std::string(2, Uint4HexValue(upper)).append(ByteHexValue(lower));
}

std::string Chip8::Hex::OpcodeHexValue(std::uint16_t opcode)
{
    const std::uint8_t upper = (opcode & 0xFF00) >> 8;
    const std::uint8_t lower = opcode & 0x00FF;

    std::string ret;
    ret.append(ByteHexValue(upper));
    ret.append(ByteHexValue(lower));

    return ret;
}

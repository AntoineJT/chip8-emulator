#pragma once
#include <string>
#include <cstdint>

namespace Chip8::Hex
{
    char Uint4HexValue(std::uint8_t hexInt);
    std::string ByteHexValue(std::uint8_t byte);
    std::string AddrHexValue(std::uint16_t nnn);
    std::string OpcodeHexValue(std::uint16_t opcode);
}

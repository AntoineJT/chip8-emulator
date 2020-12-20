#pragma once
#include <cstdint>
#include <string>

namespace Chip8::Hex
{
    char Uint4HexValue(std::uint8_t hexInt) noexcept;
    std::string ByteHexValue(std::uint8_t byte) noexcept;
    std::string AddrHexValue(std::uint16_t nnn) noexcept;
    std::string OpcodeHexValue(std::uint16_t opcode) noexcept;
}

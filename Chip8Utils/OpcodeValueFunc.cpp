#include "OpcodeValueFunc.hpp"

std::uint16_t Chip8::Utils::OpcodeValue(const std::uint8_t upper, const std::uint8_t lower)
{
    return static_cast<std::uint16_t>(upper << 8 | lower);
}

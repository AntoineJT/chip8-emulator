#pragma once

#include <cstdint>

namespace Chip8::Utils
{
    std::uint16_t OpcodeValue(std::uint8_t upper, std::uint8_t lower) noexcept;
}

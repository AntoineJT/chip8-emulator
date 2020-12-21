#pragma once
#include <cstdint>
#include <string>
#include <sstream>

namespace Chip8::Hex
{
    char Uint4HexValue(std::uint8_t hexInt) noexcept;
    std::string ByteHexValue(std::uint8_t byte) noexcept;
    std::string AddrHexValue(std::uint16_t nnn) noexcept;
    std::string OpcodeHexValue(std::uint16_t opcode) noexcept;

    template<typename T>
    std::string ToHex(const T number) noexcept
    {
        static_assert(std::is_arithmetic<T>::value, "ToHex only accepts numeric types!");

        std::ostringstream stream;
        stream << "0x" << std::hex << std::to_string(number);
        return stream.str();
    }
}

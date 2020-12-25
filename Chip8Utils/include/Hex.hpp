#pragma once
#include <cstdint>
#include <string>
#include <sstream>

namespace Chip8::Hex
{
    char Uint4HexValue(std::uint8_t hexInt) noexcept;
    std::string AddrHexValue(std::uint16_t nnn);

    template<typename T>
    std::string ToHex(const T number)
    {
        static_assert(std::is_arithmetic<T>::value, "ToHex only accepts numeric types!");

        std::ostringstream stream;
        stream << "0x" << std::hex << std::to_string(number);
        return stream.str();
    }

    constexpr auto U16ToHex = Chip8::Hex::ToHex<std::uint16_t>;
    constexpr auto U8ToHex = Chip8::Hex::ToHex<std::uint8_t>;
}

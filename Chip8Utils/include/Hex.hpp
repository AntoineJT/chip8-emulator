#pragma once
#include <cstdint>
#include <string>
#include <sstream>

namespace Chip8::Hex
{
    char Uint4HexValue(std::uint8_t hexInt);
    std::string AddrHexValue(std::uint16_t nnn);

    // based on https://stackoverflow.com/questions/5100718/integer-to-hex-string-in-c
    template <typename Integer>
    std::string IntegerToHex(const Integer number) {
        static_assert(std::is_arithmetic<Integer>::value, "IntegerToHex only accepts numeric types!");

        const std::size_t hex_len = sizeof(Integer) << 1;
        static const char* digits = "0123456789ABCDEF";

        std::string rc(hex_len, '0');
        std::size_t offset = (hex_len - 1) * 4;
        for (std::size_t i = 0; i < hex_len; ++i) {
            rc[i] = digits[(number >> offset) & 0x0F];
            offset -= 4;
        }
        return rc;
    }

    constexpr auto U16ToHex = Chip8::Hex::IntegerToHex<std::uint16_t>;
    constexpr auto U8ToHex = Chip8::Hex::IntegerToHex<std::uint8_t>;
}

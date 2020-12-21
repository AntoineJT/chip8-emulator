#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace Chip8
{
    class Memory
    {
        static constexpr std::size_t fontset_location = 0x0000;

        void LoadFontSet() noexcept;

    public:
        static constexpr std::size_t ram_size = 4096;
        using MemoryData = std::array<uint8_t, ram_size>;

        Memory() noexcept;
        void LoadProgram(const std::vector<char>& data) noexcept;
        std::uint16_t NextInstruction() const noexcept;

        MemoryData memory;

        // Pointers
        std::uint16_t pc; // program counter
        std::uint8_t sp; // stack pointer

        // Registers
        /* the VF register should not be accessed
           by a program directly, but only by
           the emulator itself.
           It is used as a flag for some
           instructions.
         */
        std::array<uint8_t, 16> VX; // usual registers
        std::uint16_t I; // the I register, generally used to store memory addresses.
        std::array<uint16_t, 16> stack;

        std::uint8_t DT; // delay timer
        std::uint8_t ST; // sound timer
    };
}

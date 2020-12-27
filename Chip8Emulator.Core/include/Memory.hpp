#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace Chip8
{
    class Memory
    {
        // TODO Support ETI 660 if some ROMs still exists on the Internet
        // See here: http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#2.1
        // Begins at 0x200, because generally
        // from 0x000 to 0x1FF, the memory was
        // reserved for the interpreter
        static constexpr std::size_t entry_point = 0x200; // 512

        void LoadFontSet() noexcept;

    public:
        static constexpr std::size_t ram_size = 4096;
        static constexpr std::size_t fontset_location = 0x0;
        using MemoryData = std::array<uint8_t, ram_size>;

        Memory() noexcept;
        void LoadProgram(const std::vector<char>& data) noexcept;
        std::uint16_t NextInstruction() const noexcept;

        MemoryData memory = {0};

        // Pointers
        std::uint16_t pc = entry_point; // program counter
        std::uint8_t sp = 0;            // stack pointer

        // Registers
        /* the VF register should not be accessed
           by a program directly, but only by
           the emulator itself.
           It is used as a flag for some
           instructions.
         */
        std::array<uint8_t, 16> VX = {0}; // usual registers
        std::uint16_t I = 0; // the I register, generally used to store memory addresses.
        std::array<uint16_t, 16> stack = {0};

        std::uint8_t DT = 0; // delay timer
        std::uint8_t ST = 0; // sound timer
    };
}

#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include "utils/byte.hpp"

namespace Chip8
{
    class Memory
    {
        static constexpr std::size_t ram_size = 4096;

    public:
        using MemoryData = std::array<byte_t, ram_size>;

        // from http://devernay.free.fr/hacks/chip8/C8TECH10.HTM
        static constexpr std::array<byte_t, 80> font_set =
        {
            0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
            0x20, 0x60, 0x20, 0x20, 0x70, // 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
            0x90, 0x90, 0xF0, 0x10, 0x10, // 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
            0xF0, 0x10, 0x20, 0x40, 0x40, // 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
            0xF0, 0x90, 0xF0, 0x90, 0x90, // A
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
            0xF0, 0x80, 0x80, 0x80, 0xF0, // C
            0xE0, 0x90, 0x90, 0x90, 0xE0, // D
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
            0xF0, 0x80, 0xF0, 0x80, 0x80 // F
        };

#define V(x) V##x = 0x##x
        enum vx {
            V(0),
            V(1),
            V(2),
            V(3),
            V(4),
            V(5),
            V(6),
            V(7),
            V(8),
            V(9),
            V(A),
            V(B),
            V(C),
            V(D),
            V(E),
            /* the VF register should not be accessed
               by a program directly, but only by
               the emulator itself.
               It is used as a flag for some
               instructions.
             */
             V(F)
        };
#undef V

        Memory();
        
        MemoryData memory;
        // Pointers
        std::uint16_t pc; // program counter
        std::uint8_t sp; // stack pointer
        // Registers
        std::array<byte_t, 16> VX; // usual registers
        std::uint16_t I; // the I register, generally used to store memory addresses.
        byte_t DT; // delay timer
        byte_t ST; // sound timer
    };
}

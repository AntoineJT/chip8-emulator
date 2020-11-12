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
        std::array<uint16_t, 16> stack;
        byte_t DT; // delay timer
        byte_t ST; // sound timer
    };
}

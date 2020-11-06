#pragma once
#include <array>
#include <cstdint>
#include "utils/byte.hpp"

namespace Chip8
{
    struct Registers
    {
        enum Vx {
            V0 = 0,
            V1 = 1,
            V2 = 2,
            V3 = 3,
            V4 = 4,
            V5 = 5,
            V6 = 6,
            V7 = 7,
            V8 = 8,
            V9 = 9,
            VA = 10,
            VB = 11,
            VC = 12,
            VD = 13,
            VE = 14,
            /* the VF register should not be accessed 
               by a program directly, but only by 
               the emulator itself.
               It is used as a flag for some 
               instructions.
             */
            VF = 15
        };

    private:
        // usual registers
        std::array<byte_t, 16> m_Vx;

        // the I register, generally used to store memory addresses.
        std::uint16_t m_I;

        // TODO Search for friend classes to maybe use them
        // delay timer
        byte_t m_DT;
        // sound timer
        byte_t m_ST;
    };
};

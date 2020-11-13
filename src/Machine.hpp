#pragma once
#include <cstdint>

#include "Memory.hpp"
#include "Screen.hpp"

namespace Chip8
{
    class Screen;
    class Memory;

    class Machine
    {
        Screen m_screen;
        Memory m_memory;

        enum instruction
        {
            SYS = 0x0000,       // 0nnn; ignored
            CLS = 0x00E0,       // 00E0; CLS
            RET = 0x00EE,       // 00EE; RET
            JP = 0x1000,        // 1nnn; JP addr
            CALL = 0x2000,      // 2nnn; CALL addr
            SE_XKK = 0x3000,    // 3xkk; SE Vx, byte
            SNE_XKK = 0x4000,   // 4xkk; SNE Vx, byte
            SE_XY = 0x5000,     // 5xy0; SE Vx, Vy
            LD_XKK = 0x6000,    // 6xkk; LD Vx, byte
            ADD_XKK = 0x7000,   // 7xkk; ADD Vx, byte
            LD_XY = 0x8000,     // 8xy0; LD Vx, Vy
            OR = 0x8001,        // 8xy1; OR Vx, Vy
            AND_XY = 0x8002,    // 8xy2; AND Vx, Vy
            XOR = 0x8003,       // 8xy3; XOR Vx, Vy
            ADD_XY = 0x8004,    // 8xy4; ADD Vx, Vy
            SUB = 0x8005,       // 8xy5; SUB Vx, Vy
            SHR = 0x8006,       // 8xy6; SHR Vx, Vy
            SUBN = 0x8007,      // 8xy7; SUBN Vx, Vy
            SHL = 0x800E,       // 8xyE; SHL Vx, Vy
            SNE_XY = 0x9000,    // 9xy0; SNE Vx, Vy
            LD_I = 0xA000,      // Annn; LD I, addr
            JP_V0 = 0xB000,     // Bnnn; JP V0, addr
            RND = 0xC000,       // Cxkk; RND Vx, byte
            DRW = 0xD000,       // Dxyn; DRW Vx, Vy, nibble
            SKP = 0xE09E,       // Ex9E; SKP Vx
            SKNP = 0xE0A1,      // ExA1; SKNP Vx
            LD_XD = 0xF007,     // Fx07; LD Vx, DT
            LD_XK = 0xF00A,     // Fx0A; LD Vx, K
            LD_DX = 0xF015,     // Fx15; LD DT, Vx
            LD_SX = 0xF018,     // Fx18; LD ST, Vx
            ADD_IX = 0xF01E,    // Fx1E; ADD I, Vx
            LD_FX = 0xF029,     // Fx29; LD F, Vx
            LD_BX = 0xF033,     // Fx33; LD B, Vx
            LD_IX = 0xF055,     // Fx55; LD [I], Vx
            LD_XI = 0xF065      // Fx65; LD Vx, [I]
        };

    public:
        Machine(Screen screen, Memory memory);

        void ExecuteNextInstruction();
        void Execute(std::uint16_t opcode);
    };
}

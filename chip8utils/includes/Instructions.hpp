#pragma once
#include <cstdint>

namespace Chip8::Utils::Instructions
{
    // these opcodes are used to make the switch statements
    // more readables
    constexpr std::uint16_t
        SYS     = 0x0000, // 0nnn; ignored
        CLS     = 0x00E0, // 00E0; CLS
        RET     = 0x00EE, // 00EE; RET
        JP      = 0x1000, // 1nnn; JP addr
        CALL    = 0x2000, // 2nnn; CALL addr
        SE_XKK  = 0x3000, // 3xkk; SE Vx, byte
        SNE_XKK = 0x4000, // 4xkk; SNE Vx, byte
        SE_XY   = 0x5000, // 5xy0; SE Vx, Vy
        LD_XKK  = 0x6000, // 6xkk; LD Vx, byte
        ADD_XKK = 0x7000, // 7xkk; ADD Vx, byte
        LD_XY   = 0x0,    // 8xy0; LD Vx, Vy
        OR      = 0x1,    // 8xy1; OR Vx, Vy
        AND_XY  = 0x2,    // 8xy2; AND Vx, Vy
        XOR     = 0x3,    // 8xy3; XOR Vx, Vy
        ADD_XY  = 0x4,    // 8xy4; ADD Vx, Vy
        SUB     = 0x5,    // 8xy5; SUB Vx, Vy
        SHR     = 0x6,    // 8xy6; SHR Vx, Vy
        SUBN    = 0x7,    // 8xy7; SUBN Vx, Vy
        SHL     = 0xE,    // 8xyE; SHL Vx, Vy
        SNE_XY  = 0x9000, // 9xy0; SNE Vx, Vy
        LD_I    = 0xA000, // Annn; LD I, addr
        JP_V0   = 0xB000, // Bnnn; JP V0, addr
        RND     = 0xC000, // Cxkk; RND Vx, byte
        DRW     = 0xD000, // Dxyn; DRW Vx, Vy, nibble
        SKP     = 0x9E,   // Ex9E; SKP Vx
        SKNP    = 0xA1,   // ExA1; SKNP Vx
        LD_XD   = 0x7,    // Fx07; LD Vx, DT
        LD_XK   = 0xA,    // Fx0A; LD Vx, K
        LD_DX   = 0x15,   // Fx15; LD DT, Vx
        LD_SX   = 0x18,   // Fx18; LD ST, Vx
        ADD_IX  = 0x1E,   // Fx1E; ADD I, Vx
        LD_FX   = 0x29,   // Fx29; LD F, Vx
        LD_BX   = 0x33,   // Fx33; LD B, Vx
        LD_IX   = 0x55,   // Fx55; LD [I], Vx
        LD_XI   = 0x65    // Fx65; LD Vx, [I]
        ;
}

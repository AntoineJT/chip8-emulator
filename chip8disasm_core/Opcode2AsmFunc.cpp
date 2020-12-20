#include "include/Opcode2AsmFunc.hpp"
#include "include/Hex.hpp"

#include <stdexcept>

#include "Instructions.hpp"

// here I think it is a good
// using namespace use case
using namespace Chip8::Utils::Instructions;

enum request
{
    X,
    XY,
    XKK,
    NNN
};

std::string GetOperands(uint16_t opcode, const request req)
{
    const std::uint8_t x = (opcode & 0x0F00) >> 8;
    const std::string xHex(1, Chip8::Hex::Uint4HexValue(x));

    switch(req)
    {
    case X:
        return "0x" + xHex;
    case XY:
        {
            const std::uint8_t y = (opcode & 0x00F0) >> 4;
            return "0x" + xHex + ", 0x" + Chip8::Hex::Uint4HexValue(y);
        }
    case XKK:
        {
            const std::uint8_t kk = opcode & 0x00FF;
            return "0x" + xHex + ", 0x" + Chip8::Hex::ByteHexValue(kk);
        }
    case NNN:
        {
            const std::uint16_t nnn = opcode & 0x0FFF;
            return "0x" + Chip8::Hex::AddrHexValue(nnn);
        }
    default:
        throw std::runtime_error("GetOperands: bad request");
    }
}

std::string DrawOperands(uint16_t opcode)
{
    const std::uint8_t lsb = opcode & 0x000F; // least significant bit
    return GetOperands(opcode, XY) + ", 0x" + Chip8::Hex::Uint4HexValue(lsb);
}

std::string UnknownOpcode(uint16_t opcode)
{
    return "; Unknown Opcode: " + Chip8::Hex::OpcodeHexValue(opcode);
}

std::string Chip8::Disasm::Opcode2Asm(std::uint16_t opcode)
{
    switch (opcode & 0xF000)
    {
    case 0x0000:
    {
        switch(opcode)
        {
        case CLS:
            return "CLS";
        case RET:
            return "RET";

        // SYS is 0NNN
        default:
            return "SYS " + GetOperands(opcode, NNN);
        }
    }
    case JP:
        return "JP " + GetOperands(opcode, NNN);
    case CALL:
        return "CALL " + GetOperands(opcode, NNN);
    case SE_XKK:
        return "SE " + GetOperands(opcode, XKK) + " ; XKK";
    case SNE_XKK:
        return "SNE " + GetOperands(opcode, XKK) + " ; XKK";
    case SE_XY:
        return "SE " + GetOperands(opcode, XY) + " ; XY";
    case LD_XKK:
        return "LD " + GetOperands(opcode, XKK) + " ; XKK";
    case ADD_XKK:
        return "ADD " + GetOperands(opcode, XKK) + " ; XKK";
    case 0x8000:
    {
        const std::uint8_t lsb = opcode & 0x000F; // least significant bit
        switch (lsb)
        {
        case LD_XY:
            return "LD " + GetOperands(opcode, XY) + " ; XY";
        case OR:
            return "OR " + GetOperands(opcode, XY);
        case AND_XY:
            return "AND " + GetOperands(opcode, XY) + " ; XY";
        case XOR:
            return "XOR " + GetOperands(opcode, XY);
        case ADD_XY:
            return "ADD " + GetOperands(opcode, XY) + " ; XY";
        case SUB:
            return "SUB " + GetOperands(opcode, XY);
        case SHR:
            return "SHR " + GetOperands(opcode, XY);
        case SUBN:
            return "SUBN " + GetOperands(opcode, XY);
        case SHL:
            return "SHL " + GetOperands(opcode, XY);
        default:
            break;
        }
        return UnknownOpcode(opcode);
    }
    case SNE_XY:
        return "SNE " + GetOperands(opcode, XY) + " ; XY";
    case LD_I:
        return "LD I, " + GetOperands(opcode, NNN);
    case JP_V0:
        return "JP V0, " + GetOperands(opcode, NNN);
    case RND:
        return "RND " + GetOperands(opcode, XKK);
    case DRW:
        return "DRW " + DrawOperands(opcode);
    case 0xE000:
    {
        const std::uint8_t kk = opcode & 0x00FF;
        if (kk == SKP)
            return "SKP " + GetOperands(opcode, X);
        if (kk == SKNP)
            return "SKNP " + GetOperands(opcode, X);
        return UnknownOpcode(opcode);
    }
    case 0xF000:
    {
        switch (opcode & 0x00FF)
        {
        case LD_XD:
            return "LD " + GetOperands(opcode, X) + ", DT";
        case LD_XK:
            return "LD " + GetOperands(opcode, X) + ", K";
        case LD_DX:
            return "LD DT, " + GetOperands(opcode, X);
        case LD_SX:
            return "LD ST, " + GetOperands(opcode, X);
        case ADD_IX:
            return "ADD I, " + GetOperands(opcode, X);
        case LD_FX:
            return "LD F, " + GetOperands(opcode, X);
        case LD_BX:
            return "LD B, " + GetOperands(opcode, X);
        case LD_IX:
            return "LD [I], " + GetOperands(opcode, X);
        case LD_XI:
            return "LD " + GetOperands(opcode, X) + ", [I]";
        default:
            break;
        }
        return UnknownOpcode(opcode);
    }

    default:
        return UnknownOpcode(opcode);
    }
}

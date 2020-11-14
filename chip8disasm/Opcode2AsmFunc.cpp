#include "Opcode2AsmFunc.hpp"
#include "Instructions.hpp"
#include "Hex.hpp"

// here I think it is a good
// using namespace usage
using namespace Chip8::Instructions;

std::string Chip8::Disasm::Opcode2Asm(std::uint16_t opcode)
{
    const std::uint8_t x = (opcode & 0x0F00) >> 8;
    const std::uint8_t y = (opcode & 0x00F0) >> 4;
    const std::uint8_t kk = opcode & 0x00FF;
    const std::uint8_t lsb = opcode & 0x000F; // least significant bit
    const std::uint16_t nnn = opcode & 0x0FFF;

    const std::string opcodeHex = Hex::OpcodeHexValue(opcode);
    const std::string nnnHex = Hex::AddrHexValue(nnn);
    const std::string kkHex = Hex::ByteHexValue(kk);
    const std::string xHex = std::to_string(Hex::Uint4HexValue(x));
    const std::string yHex = std::to_string(Hex::Uint4HexValue(y));
    const std::string lsbHex = std::to_string(Hex::Uint4HexValue(lsb));

    const std::string UNKNOWN = "; Unknown Opcode: " + opcodeHex;

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
        case SYS:
            return "SYS 0x" + opcodeHex;
        default:
            break;
        }
        return UNKNOWN;
    }
    case JP:
        return "JP 0x" + nnnHex;
    case CALL:
        return "CALL 0x" + nnnHex;
    case SE_XKK:
        return "SE 0x" + xHex + ", 0x" + kkHex + " ; XKK";
    case SNE_XKK:
        return "SNE 0x" + xHex + ", 0x" + kkHex + " ; XKK";
    case SE_XY:
        return "SE 0x" + xHex + ", 0x" + yHex + " ; XY";
    case LD_XKK:
        return "LD 0x" + xHex + ", 0x", yHex + " ; XKK";
    case ADD_XKK:
        return "ADD 0x" + xHex + ", 0x" + yHex + " ; XKK";
    case 0x8000:
    {
        switch (lsb)
        {
        case LD_XY:
            return "LD 0x" + xHex + ", 0x" + yHex + " ; XY";
        case OR:
            return "OR 0x" + xHex + ", 0x" + yHex;
        case AND_XY:
            return "AND 0x" + xHex + ", 0x" + yHex + " ; XY";
        case XOR:
            return "XOR 0x" + xHex + ", 0x" + yHex;
        case ADD_XY:
            return "ADD 0x" + xHex + ", 0x" + yHex + " ; XY";
        case SUB:
            return "SUB 0x" + xHex + ", 0x" + yHex;
        case SHR:
            return "SHR 0x" + xHex + ", 0x" + yHex;
        case SUBN:
            return "SUBN 0x" + xHex + ", 0x" + yHex;
        case SHL:
            return "SHL 0x" + xHex + ", 0x" + yHex;
        default:
            break;
        }
        return UNKNOWN;
    }
    case SNE_XY:
        return "SNE 0x" + xHex + ", 0x" + yHex + " ; XY";
    case LD_I:
        return "LD I, 0x" + nnnHex;
    case JP_V0:
        return "JP V0, 0x" + nnnHex;
    case RND:
        return "RND 0x" + xHex + ", 0x" + kkHex;
    case DRW:
        return "DRW 0x" + xHex + ", 0x" + yHex + ", 0x" + lsbHex;
    case 0xE000:
    {
        if (kk == SKP)
            return "SKP 0x" + xHex;
        if (kk == SKNP)
            return "SKNP 0x" + xHex;
        return UNKNOWN;
    }
    case 0xF000:
    {
        switch (opcode & 0x00FF)
        {
        case LD_XD:
            return "LD 0x" + xHex + ", DT";
        case LD_XK:
            return "LD 0x" + xHex + ", K";
        case LD_DX:
            return "LD DT, 0x" + xHex;
        case LD_SX:
            return "LD ST, 0x" + xHex;
        case ADD_IX:
            return "ADD I, 0x" + xHex;
        case LD_FX:
            return "LD F, 0x" + xHex;
        case LD_BX:
            return "LD B, 0x" + xHex;
        case LD_IX:
            return "LD [I], 0x" + xHex;
        case LD_XI:
            return "LD 0x" + xHex + ", [I]";
        default:
            break;
        }
        return UNKNOWN;
    }

    default:
        return UNKNOWN;
    }
}

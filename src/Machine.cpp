#include "Machine.hpp"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <random>

Chip8::Machine::Machine(Screen screen, Memory memory)
    : m_screen(screen)
    , m_memory(memory)
{}

void Chip8::Machine::Execute(const uint16_t opcode)
{
#define PRINT_UNKNOWN_OPCODE
    std::cerr << "Err: Unknown instruction (" \
        << std::hex << opcode << std::dec \
        << std::endl;

    const std::uint8_t x = (opcode & 0x0F00) >> 8;
    const std::uint8_t y = (opcode & 0x00F0) >> 4;
    const std::uint8_t kk = opcode & 0x00FF;
    const std::uint8_t lsb = opcode & 0x000F; // least significant bit
    const std::uint16_t nnn = opcode & 0x0FFF;

    uint8_t incBy = 1;

    switch(opcode & 0xF000)
    {
    case 0x0000:
        {
            // CLS
            if (opcode == CLS)
            {
                m_screen.Refresh(true);
                break;
            }

            // RET
            if (opcode == RET)
            {
                assert(m_memory.sp > 0);
                m_memory.pc = m_memory.stack[m_memory.sp];
                --m_memory.sp;
                break;
            }

            // SYS
            if (opcode == SYS)
            {
                // this is ignored, only used on real machine
                break;
            }

            PRINT_UNKNOWN_OPCODE
        }

    case JP:
        m_memory.pc = nnn;
        incBy = 0;
        break;

    case CALL:
        ++m_memory.sp;
        m_memory.stack[m_memory.sp] = m_memory.pc;
        m_memory.pc = nnn;
        incBy = 0;
        break;

    case SE_XKK:
        if (m_memory.VX[x] == kk)
        {
            incBy = 2;
        }
        break;

    case SNE_XKK:
        if (m_memory.VX[x] != kk)
        {
            incBy = 2;
        }
        break;

    case SE_XY:
        if (m_memory.VX[x] == m_memory.VX[y])
        {
            incBy = 2;
        }
        break;

    case LD_XKK:
        m_memory.VX[x] = kk;
        break;

    case ADD_XKK:
        m_memory.VX[x] += kk;
        break;

    case 0x8000:
        {
            switch(lsb)
            {
            // LD_XY
            case 0x0:
                m_memory.VX[x] = m_memory.VX[y];
                break;

            // OR
            case 0x1:
                m_memory.VX[x] |= m_memory.VX[y];
                break;

            // AND_XY
            case 0x2:
                m_memory.VX[x] &= m_memory.VX[y];
                break;

            // XOR
            case 0x3:
                m_memory.VX[x] ^= m_memory.VX[y];
                break;

            // ADD_XY
            case 0x4:
                {
                    const std::uint16_t sum = m_memory.VX[x] + m_memory.VX[y];
                    if (sum > 0xFF)
                    {
                        m_memory.VX[0xF] = 1;
                        m_memory.VX[x] = sum - 0xFF; // not sure about that
                    }
                    else
                    {
                        m_memory.VX[0xF] = 0;
                        m_memory.VX[x] = sum;
                    }
                    break;
                }

            // SUB
            case 0x5:
                {
                    const std::int16_t sub = m_memory.VX[x] - m_memory.VX[y];
                    m_memory.VX[0xF] = (sub > 0) ? 1 : 0;
                    m_memory.VX[x] = static_cast<uint8_t>(sub); // TODO wtf? need to check how to handle this properly
                    break;
                }

            // SHR
            case 0x6:
                m_memory.VX[0xF] = m_memory.VX[x] & 0x000F;
                m_memory.VX[x] <<= 1;
                break;

            // SUBN
            case 0x7:
                {
                    const std::int16_t sub = m_memory.VX[y] - m_memory.VX[x];
                    m_memory.VX[0xF] = (sub > 0) ? 1 : 0;
                    m_memory.VX[x] = static_cast<uint8_t>(sub); // TODO wtf? need to check how to handle this properly
                    break;
                }

            // SHL
            case 0xE:
                m_memory.VX[0xF] = m_memory.VX[x] & 0x000F;
                m_memory.VX[x] >>= 1;
                break;

            default:
                PRINT_UNKNOWN_OPCODE
                break;
            }
            break;
        }

    case SNE_XY:
        if (m_memory.VX[x] != m_memory.VX[y])
        {
            incBy = 2;
        }
        break;

    case LD_I:
        m_memory.I = nnn;
        break;

    case JP_V0:
        m_memory.pc = nnn + m_memory.VX[0];
        incBy = 0;
        break;
    case RND:
        {
            // TODO Move it elsewhere, use only one rd
            // and dist instead of creating once each time
            // i.e in a class called Random
            std::random_device rd;
            const std::uniform_int_distribution<int> dist(0, 255);

            m_memory.VX[x] = dist(rd) & kk;
            break;
        }

    case DRW:
        // TODO

    case 0xE000:
        {
            // SKP
            if (kk == 0x9E)
            {
                // TODO Implement it, needs to check keyboard status (SDL)
                break;
            }

            // SKNP
            if (kk == 0xA1)
            {
                // TODO Implement it, the opposite of SKP
                break;
            }

            PRINT_UNKNOWN_OPCODE
            break;
        }
   
    case 0xF000:
        // TODO

    default:
        PRINT_UNKNOWN_OPCODE
        break;
    }

    m_memory.pc += incBy;

#undef PRINT_UNKNOWN_OPCODE
}

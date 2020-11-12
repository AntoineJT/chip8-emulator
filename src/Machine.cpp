#include "Machine.hpp"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <random>

Chip8::Machine::Machine(Screen screen, Memory memory)
    : m_screen(screen)
    , m_memory(memory)
{}

void Chip8::Machine::Execute(int16_t opcode)
{
#define PRINT_UNKNOWN_OPCODE
    std::cerr << "Err: Unknown instruction (" \
        << std::hex << opcode << std::dec \
        << std::endl;

    const std::int8_t x = (opcode & 0x0F00) >> 8;
    const std::int8_t y = (opcode & 0x00F0) >> 4;
    const std::int8_t kk = opcode & 0x00FF;
    const std::int16_t nnn = opcode & 0x0FFF;

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
        {
            m_memory.pc = nnn;
            incBy = 0;
        }
    case CALL:
        {
            ++m_memory.sp;
            m_memory.stack[m_memory.sp] = m_memory.pc;
            m_memory.pc = nnn;
            incBy = 0;
        }
    case SE_XKK:
        {
            if (m_memory.VX[x] == kk)
            {
                incBy = 2;
            }
        }
    case SNE_XKK:
        {
            if (m_memory.VX[x] != kk)
            {
                incBy = 2;
            }
        }
    case SE_XY:
        {
            if (m_memory.VX[x] == m_memory.VX[y])
            {
                incBy = 2;
            }
        }
    case LD_XKK:
        {
            m_memory.VX[x] = kk;
        }
    case ADD_XKK:
        {
            m_memory.VX[x] += kk;
        }
    case 0x8000:
        // TODO
    case SNE_XY:
        {
            if (m_memory.VX[x] != m_memory.VX[y])
            {
                incBy = 2;
            }
        }
    case LD_I:
        {
            m_memory.I = nnn;
        }
    case JP_V0:
        {
            m_memory.pc = nnn + m_memory.VX[0];
            incBy = 0;
        }
    case RND:
        {
            // TODO Move it elsewhere, use only one rd
            // and dist instead of creating once each time
            // i.e in a class called Random
            std::random_device rd;
            std::uniform_int_distribution<uint8_t> dist(0, 255);

            m_memory.VX[x] = dist(rd) & kk;
        }
    case DRW:
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
                // TODO Implement it, same as SKP but the opposite
                break;
            }

            PRINT_UNKNOWN_OPCODE
        }
    case 0xF000:
    default:
        PRINT_UNKNOWN_OPCODE
        break;
    }

    m_memory.pc += incBy;

#undef PRINT_UNKNOWN_OPCODE
}

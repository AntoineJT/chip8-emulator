#include "Machine.hpp"

#include <cassert>
#include <cstdint>

Chip8::Machine::Machine(Screen screen, Memory memory)
    : m_screen(screen)
    , m_memory(memory)
{}

void Chip8::Machine::Execute(int16_t opcode)
{
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
            // this is ignored, only used on real machine
        }
    case JP:
        {
            m_memory.pc = opcode & 0x0FFF;
        }
    case CALL:
        {
            ++m_memory.sp;
            m_memory.stack[m_memory.sp] = m_memory.pc;
            m_memory.pc = opcode & 0x0FFF;
        }
    case SE_XKK:
        {
            const std::int8_t x = (opcode & 0x0F00) >> 8;
            const std::int8_t kk = opcode & 0x00FF;

            if (m_memory.VX[x] == kk)
            {
                incBy = 2;
                break;
            }
        }
    case SNE_XKK:
    case SE_XY:
    case LD_XKK:
    case ADD_XKK:
    case 0x8000:
    case SNE_XY:
    case LD_I:
    case JP_V0:
    case RND:
    case DRW:
    case 0xE000:
    case 0xF000:
    default:
        break;
    }

    m_memory.pc += incBy;
}

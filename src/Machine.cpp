#include "Machine.hpp"

#include <cassert>
#include <cstdint>

Chip8::Machine::Machine(Screen screen, Memory memory)
    : m_screen(screen)
    , m_memory(memory)
{}

void Chip8::Machine::Execute(int16_t opcode)
{
    switch(opcode & 0xF000)
    {
    case 0x0000:
        {
            // CLS
            if (opcode == CLS)
            {
                m_screen.Refresh(true);
                return;
            }

            // RET
            if (opcode == RET)
            {
                assert(m_memory.sp > 0);
                m_memory.pc = m_memory.sp;
                --m_memory.sp;
                // return;
            }

            // SYS
            // this is ignored, only used on real machine
        }
    case 0x1000:
    case CALL:
    case SE_XKK:
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
}

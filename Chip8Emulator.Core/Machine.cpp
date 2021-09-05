#include "Machine.hpp"

#include <iostream>
#include <sdl_assert.h>

#include "Instructions.hpp"
#include "Keyboard.hpp"

// I think it suits to the use case
using namespace Chip8::Utils::Instructions;

Chip8::Machine::Machine(std::shared_ptr<Screen> screen, std::shared_ptr<Memory> memory, std::shared_ptr<Keyboard> keyboard)
    : m_memoryPtr(memory)
    , m_memory(*memory.get())
    , m_keyboard(*keyboard.get())
    , m_cpu(CPU(screen, memory, keyboard))
{}

void Chip8::Machine::ExecuteNextInstruction()
{
    Execute(m_memory.NextInstruction());
    // TODO S'occuper des timers
}

// TODO Rename it to something like UnfreezeWindows
void Chip8::Machine::HandleEvents()
{
    while (SDL_PollEvent(&m_event)) {
        switch (m_event.type) {
        case SDL_QUIT:
            exit(0);
        case SDL_KEYDOWN:
        {
            const std::unordered_map<SDL_Scancode, Key>& map = m_keyboard.m_keymap.ReversedData();
            const auto elem = map.find(m_event.key.keysym.scancode);
            if (elem != map.end())
            {
                m_keyboard.m_state.hasPressedKey = true;
                m_keyboard.m_state.keyPressed = elem->second;
            }
            break;
        }
        default:
            break;
        }
    }
}

void PrintOpcodeStatus(const char* status, const std::uint16_t opcode)
{
    std::cerr << "Err: " << status << " instruction ("
        << std::hex << opcode << std::dec << ")"
        << std::endl;
}

void Chip8::Machine::Execute(const std::uint16_t opcode)
{
    std::cout << "Info: Opcode '" << std::hex << opcode << std::dec << "' next!" << std::endl;

    const std::uint8_t x = (opcode & 0x0F00) >> 8;
    const std::uint8_t y = (opcode & 0x00F0) >> 4;
    const std::uint8_t kk = opcode & 0x00FF;
    const std::uint8_t ls4b = opcode & 0x000F; // least significant 4 bits
    const std::uint16_t nnn = opcode & 0x0FFF;

    std::uint8_t incBy = 2;

    switch(opcode & 0xF000)
    {
    case 0x0000:
        switch(opcode)
        {
        case CLS:
            m_cpu.CLS();
            break;

        case RET:
            m_cpu.RET();
            break;

        default:
            // SYS is 0NNN so all that remains after CLS and RET
            // this is ignored, only used on real machine
            PrintOpcodeStatus("Ignored", opcode);
            break;
        }
        break;

    case JP:
        m_cpu.JP(nnn);
        incBy = 0;
        break;

    case CALL:
        m_cpu.CALL(nnn);
        incBy = 0;
        break;

    case SE_XKK:
        if (m_memory.VX[x] == kk)
        {
            incBy = 4;
        }
        break;

    case SNE_XKK:
        if (m_memory.VX[x] != kk)
        {
            incBy = 4;
        }
        break;

    case SE_XY:
        if (m_memory.VX[x] == m_memory.VX[y])
        {
            incBy = 4;
        }
        break;

    case LD_XKK:
        m_cpu.LD_XKK(x, kk);
        break;

    case ADD_XKK:
        m_cpu.ADD_XKK(x, kk);
        break;

    case 0x8000:
        switch(ls4b)
        {
        case LD_XY:
            m_cpu.LD_XY(x, y);
            break;

        case OR:
            m_cpu.OR(x, y);
            break;

        case AND_XY:
            m_cpu.AND_XY(x, y);
            break;

        case XOR:
            m_cpu.XOR(x, y);
            break;

        case ADD_XY:
            m_cpu.ADD_XY(x, y);
            break;

        case SUB:
            m_cpu.SUB(x, y);
            break;

        case SHR:
            m_cpu.SHR(x);
            break;

        case SUBN:
            m_cpu.SUBN(x, y);
            break;

        case SHL:
            m_cpu.SHL(x);
            break;

        default:
            PrintOpcodeStatus("Unknown", opcode);
            break;
        }
        break;

    case SNE_XY:
        if (m_memory.VX[x] != m_memory.VX[y])
        {
            incBy = 4;
        }
        break;

    case LD_I:
        m_cpu.LD_I(nnn);
        break;

    case JP_V0:
        m_cpu.JP_V0(nnn);
        incBy = 0;
        break;

    case RND:
        m_cpu.RND(x, kk);
        break;

    case DRW:
        m_cpu.DRW(ls4b, x, y);
        break;

    case 0xE000:
        {
            if (kk == SKP)
            {
                // TODO Implement it, needs to check keyboard status (SDL)
                m_cpu.SKP(x);
                // PrintOpcodeStatus("Unhandled", opcode);
                break;
            }

            if (kk == SKNP)
            {
                // TODO Implement it, the opposite of SKP
                PrintOpcodeStatus("Unhandled", opcode);
                break;
            }

            PrintOpcodeStatus("Unknown", opcode);
            break;
        }
   
    case 0xF000:
        switch(opcode & 0x00FF)
        {
        case LD_XD:
            m_cpu.LD_XD(x);
            break;

        case LD_XK:
            // TODO Wait for a key press by pausing the program then
            // store the value of the key into Vx
            // PrintOpcodeStatus("Unhandled", opcode);
            break;

        case LD_DX:
            m_cpu.LD_DX(x);
            break;

        case LD_SX:
            m_cpu.LD_SX(x);
            break;

        case ADD_IX:
            m_cpu.ADD_IX(x);
            break;

        case LD_FX:
            m_cpu.LD_FX(x);
            break;

        case LD_BX:
            m_cpu.LD_BX(x);
            break;

        case LD_IX:
            m_cpu.LD_IX(x);
            break;

        case LD_XI:
            m_cpu.LD_XI(x);
            break;

        default:
            PrintOpcodeStatus("Unknown", opcode);
            break;
        }
        break;

    default:
        PrintOpcodeStatus("Unknown", opcode);
        break;
    }

    m_memory.pc += incBy;
}

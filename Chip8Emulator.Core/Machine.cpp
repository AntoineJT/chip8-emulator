#include "Machine.hpp"

#include <iostream>

#include "Instructions.hpp"
#include "Keyboard.hpp"
#include "LoadFileFunc.hpp"
#include "Hex.hpp"

#include <sdl_assert.h>

// I think it suits to the use case
using namespace Chip8::Utils::Instructions;

Chip8::Machine::Machine(std::shared_ptr<Screen> screen, std::shared_ptr<Memory> memory, std::shared_ptr<Keyboard> keyboard)
    : m_memoryPtr(memory)
    , m_keyboardPtr(keyboard)
    , m_cpu(CPU(screen, memory, keyboard))
{
    InitTimers();
}

Chip8::Machine::Machine(std::shared_ptr<Screen> screen, const std::string& filepath)
    : m_memoryPtr(std::make_shared<Memory>())
    , m_keyboardPtr(std::make_shared<Keyboard>())
    , m_cpu(CPU(screen, m_memoryPtr, m_keyboardPtr))
{
    std::vector<char> content;
    if (!Chip8::Utils::LoadFile(content, filepath))
    {
        exit(EXIT_FAILURE);
    }

    m_memoryPtr->LoadProgram(content);
    InitTimers();
}

// Timers are running at 60Hz
void Chip8::Machine::InitTimers()
{
    constexpr double delayMs = 1000.0 / 60;
    constexpr auto delay = static_cast<int>(delayMs * 1,000,000);
    Memory& mem = *m_memoryPtr;
    auto& dt = mem.DT;
    auto& st = mem.ST;

    m_soundTimer.setIntervalNs([&st]() {
        if (st.load(std::memory_order_acquire) > 0) {
            --st;
            // TODO Replace that with actual sound
            std::cout << "SOUND !!" << std::endl;
        }
    }, delay);
    m_delayTimer.setIntervalNs([&dt]() {
        if (dt.load(std::memory_order_acquire) > 0) {
            --dt;
        }
    }, delay);
}

void Chip8::Machine::ExecuteNextInstruction()
{
    Execute(m_memoryPtr->NextInstruction());
}

void Chip8::Machine::HandleEvents()
{
    while (SDL_PollEvent(&m_event)) {
        switch (m_event.type) {
        case SDL_KEYDOWN:
        {
            const auto& keymap = m_keyboardPtr->m_keymap;
            const auto elem = keymap.find(m_event.key.keysym.scancode);
            if (elem != keymap.end())
            {
                m_keyboardPtr->m_state.hasPressedKey = true;
                m_keyboardPtr->m_state.keyPressed = elem->second;
            }
            break;
        }
        case SDL_QUIT:
            exit(0);
        default:
            break;
        }
    }
}

void PrintOpcodeStatus(const char* status, const std::uint16_t opcode)
{
    std::cerr << "Err: " << status << " instruction ("
        << Chip8::Hex::U16ToHex(opcode) << ")"
        << std::endl;
}

void Chip8::Machine::Execute(const std::uint16_t opcode)
{
    std::cout << "Info: Opcode '" << Chip8::Hex::U16ToHex(opcode) << "' next!" << std::endl;

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
        if (m_memoryPtr->VX[x] == kk)
        {
            incBy = 4;
        }
        break;

    case SNE_XKK:
        if (m_memoryPtr->VX[x] != kk)
        {
            incBy = 4;
        }
        break;

    case SE_XY:
        if (m_memoryPtr->VX[x] == m_memoryPtr->VX[y])
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
        if (m_memoryPtr->VX[x] != m_memoryPtr->VX[y])
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
                m_cpu.SKP(x);
                break;
            }

            if (kk == SKNP)
            {
                m_cpu.SKNP(x);
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
            m_cpu.LD_XK(x);
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

    m_memoryPtr->pc += incBy;
}

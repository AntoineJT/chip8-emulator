#include "include/Machine.hpp"

#include <cassert>
#include <iostream>

#include "Instructions.hpp"

// I think it suits to the use case
using namespace Chip8::Utils::Instructions;

std::vector<Chip8::Screen::Point> PointsToDraw(const std::vector<uint8_t>& sprite, const Chip8::Screen::Point point, const uint8_t width) noexcept
{
    assert(width <= 8);
    const std::size_t size = sprite.size();

    std::vector<Chip8::Screen::Point> toDraw;

    for (std::size_t y = 0; y < size; ++y)
    {
        const std::uint8_t line = sprite[y];
        for (std::size_t x = 0; x < width; ++x)
        {
            constexpr std::uint8_t MSB = 0x80;

            const std::uint8_t offset = MSB >> x;
            const bool isOn = (line & offset) != 0;
            if (isOn)
            {
                toDraw.push_back({ x + point.first, y + point.second });
            }
        }
    }

    assert(!toDraw.empty());
    return toDraw;
}

Chip8::Machine::Machine(Screen& screen, Memory& memory) noexcept
    : m_screen(screen)
    , m_memory(memory)
    , m_cpu(CPU(screen, memory))
{}

void Chip8::Machine::ExecuteNextInstruction() noexcept
{
    Execute(m_memory.NextInstruction());
    // TODO S'occuper des timers
}

void Chip8::Machine::Execute(const std::uint16_t opcode) noexcept
{
#define PRINT_OPCODE_STATUS(case_) \
    std::cerr << "Err: " << (case_) << " instruction (" \
        << std::hex << opcode << std::dec << ")" \
        << std::endl;

    std::cout << "Info: Opcode '" << std::hex << opcode << std::dec << "' next!" << std::endl;

    const std::uint8_t x = (opcode & 0x0F00) >> 8;
    const std::uint8_t y = (opcode & 0x00F0) >> 4;
    const std::uint8_t kk = opcode & 0x00FF;
    const std::uint8_t lsb = opcode & 0x000F; // least significant bit
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
            PRINT_OPCODE_STATUS("Ignored")
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
        switch(lsb)
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
            PRINT_OPCODE_STATUS("Unknown")
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

    // TODO Move it to CPU
    // TODO Draw: fix render being bad
    // TODO SDL: fix it crashing if clicking on the window
    case DRW:
        {
            std::vector<uint8_t> sprite(static_cast<std::size_t>(lsb) + 1);
            for (std::size_t i = 0; i <= lsb; ++i)
            {
                sprite[i] = m_memory.memory[i + m_memory.I];
            }
            const Screen::Point point(m_memory.VX[x], m_memory.VX[y]);
            const std::vector<Screen::Point> toDraw = PointsToDraw(sprite, point, 8);

            bool collides = false;
            std::vector<Screen::Point> wrappedPoints; // (toDraw.size());
            for (const auto& pt : toDraw)
            {
                const uint8_t x2 = pt.first % base_width;
                const uint8_t y2 = pt.second % base_height;
                collides |= m_screen.Collides(x2, y2);
                wrappedPoints.push_back({ x2, y2 });
            }
            m_memory.VX[0xF] = collides ? 1 : 0;
            m_screen.DrawSprite(wrappedPoints);
            m_screen.Refresh(false);
            break;
        }

    case 0xE000:
        {
            if (kk == SKP)
            {
                // TODO Implement it, needs to check keyboard status (SDL)
                PRINT_OPCODE_STATUS("Unhandled")
                break;
            }

            if (kk == SKNP)
            {
                // TODO Implement it, the opposite of SKP
                PRINT_OPCODE_STATUS("Unhandled")
                break;
            }

            PRINT_OPCODE_STATUS("Unknown")
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
            PRINT_OPCODE_STATUS("Unhandled")
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
            PRINT_OPCODE_STATUS("Unknown")
            break;
        }
        break;

    default:
        PRINT_OPCODE_STATUS("Unknown")
        break;
    }

    m_memory.pc += incBy;

#undef PRINT_OPCODE_STATUS
}

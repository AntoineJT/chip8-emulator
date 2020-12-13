#include "Machine.hpp"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <random>

#include "Instructions.hpp"

// I think it suits to the use case
using namespace Chip8::Utils::Instructions;

// TODO Find the underlying problem: sometimes it returns empty vector
std::vector<Chip8::Screen::Point> PointsToDraw(std::vector<uint8_t> sprite, const Chip8::Screen::Point point, uint8_t width)
{
    assert(width <= 8);
    const std::size_t size = sprite.size();

    std::vector<Chip8::Screen::Point> toDraw; //(size);

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

Chip8::Machine::Machine(Screen& screen, Memory& memory)
    : m_screen(screen)
    , m_memory(memory)
{}

void Chip8::Machine::ExecuteNextInstruction()
{
    const std::uint8_t upper = m_memory.memory[m_memory.pc];
    const std::uint8_t lower = m_memory.memory[static_cast<std::size_t>(m_memory.pc) + 1];
    const std::uint16_t opcode = (upper << 8) | lower;

    Execute(opcode);
    // TODO S'occuper des timers
}

void Chip8::Machine::Execute(std::uint16_t opcode)
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
        {
            switch(opcode)
            {
            case CLS:
                m_screen.Refresh(true);
                break;
            case RET:
                assert(m_memory.sp > 0);
                m_memory.pc = m_memory.stack[m_memory.sp];
                --m_memory.sp;
                break;
            default:
                // SYS is 0NNN so all that remains after CLS and RET
                // this is ignored, only used on real machine
                PRINT_OPCODE_STATUS("Ignored")
                break;
            }
            break;
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
        m_memory.VX[x] = kk;
        break;

    case ADD_XKK:
        m_memory.VX[x] += kk;
        break;

    case 0x8000:
        {
            switch(lsb)
            {
            case LD_XY:
                m_memory.VX[x] = m_memory.VX[y];
                break;

            case OR:
                m_memory.VX[x] |= m_memory.VX[y];
                break;

            case AND_XY:
                m_memory.VX[x] &= m_memory.VX[y];
                break;

            case XOR:
                m_memory.VX[x] ^= m_memory.VX[y];
                break;

            case ADD_XY:
                {
                    const std::uint16_t sum = m_memory.VX[x] + m_memory.VX[y];
                    if (sum > 0xFF)
                    {
                        m_memory.VX[0xF] = 1;
                        m_memory.VX[x] = static_cast<uint8_t>((sum - 0xFF) % 256); // not sure about that
                    }
                    else
                    {
                        m_memory.VX[0xF] = 0;
                        m_memory.VX[x] = static_cast<uint8_t>(sum);
                    }
                    break;
                }

            case SUB:
                {
                    const std::int16_t sub = m_memory.VX[x] - m_memory.VX[y];
                    m_memory.VX[0xF] = (sub > 0) ? 1 : 0;
                    m_memory.VX[x] = static_cast<uint8_t>(sub % 256); // TODO wtf? need to check how to handle this properly
                    break;
                }

            case SHR:
                m_memory.VX[0xF] = m_memory.VX[x] & 0x000F;
                m_memory.VX[x] <<= 1;
                break;

            case SUBN:
                {
                    const std::int16_t sub = m_memory.VX[y] - m_memory.VX[x];
                    m_memory.VX[0xF] = (sub > 0) ? 1 : 0;
                    m_memory.VX[x] = static_cast<uint8_t>(sub % 256); // TODO wtf? need to check how to handle this properly
                    break;
                }

            case SHL:
                m_memory.VX[0xF] = m_memory.VX[x] & 0x000F;
                m_memory.VX[x] >>= 1;
                break;

            default:
                PRINT_OPCODE_STATUS("Unknown")
                break;
            }
            break;
        }

    case SNE_XY:
        if (m_memory.VX[x] != m_memory.VX[y])
        {
            incBy = 4;
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
            
			// NOTE if those are const, then it doesn't compile
			// with gcc on linux
			std::random_device rd;
			std::uniform_int_distribution<int> dist(0, 255);

            m_memory.VX[x] = dist(rd) & kk;
            break;
        }

    // TODO Fix this
    case DRW:
        {
            std::vector<uint8_t> sprite(lsb + 1);
            for (std::size_t i = 0; i <= lsb; ++i)
            {
                sprite[i] = m_memory.memory[i + m_memory.I];
            }
            const Screen::Point point(m_memory.VX[x], m_memory.VX[y]);
            const std::vector<Screen::Point> toDraw = PointsToDraw(sprite, point, 8);

            bool collides = false;
            std::vector<Screen::Point> wrappedPoints; // (toDraw.size());
            for (const auto pt : toDraw)
            {
                const uint8_t x2 = pt.first % base_width;
                const uint8_t y2 = pt.second % base_height;
                collides |= m_screen.Collides(x2, y2);
                wrappedPoints.push_back({ x2, y2 });
            }
            m_memory.VX[0xF] = collides ? 1 : 0;
            m_screen.DrawSprite(std::move(wrappedPoints));
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
        {
            switch(opcode & 0x00FF)
            {
            case LD_XD:
                m_memory.VX[x] = m_memory.DT;
                break;

            case LD_XK:
                // TODO Wait for a key press by pausing the program then
                // store the value of the key into Vx
                PRINT_OPCODE_STATUS("Unhandled")
                break;

            case LD_DX:
                m_memory.DT = m_memory.VX[x];
                break;

            case LD_SX:
                m_memory.ST = m_memory.VX[x];
                break;

            case ADD_IX:
                m_memory.I += m_memory.VX[x];
                break;
                
            case LD_FX:
                // TODO This is the instructions to point to the fontset
                PRINT_OPCODE_STATUS("Unhandled")
                break;

            case LD_BX:
                // TODO
                PRINT_OPCODE_STATUS("Unhandled")
                break;

            case LD_IX:
                for (std::size_t i = 0; i <= x; ++i)
                {
                    m_memory.memory[m_memory.I + i] = m_memory.VX[i];
                }
                break;

            case LD_XI:
                for (std::size_t i = 0; i <= x; ++i)
                {
                    m_memory.VX[i] = m_memory.memory[m_memory.I + i];
                }
                break;

            default:
                PRINT_OPCODE_STATUS("Unknown")
                break;
            }
            break;
        }

    default:
        PRINT_OPCODE_STATUS("Unknown")
        break;
    }

    m_memory.pc += incBy;

#undef PRINT_OPCODE_STATUS
}

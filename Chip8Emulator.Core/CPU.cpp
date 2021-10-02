#include "CPU.hpp"

#include <cassert>
#include <random>
#include <utility>
#include <sdl_assert.h>

Chip8::CPU::CPU(std::shared_ptr<Screen> screen, const std::shared_ptr<Memory>& memory, const std::shared_ptr<Keyboard>& keyboard)
    : m_screenPtr(std::move(screen))
    , m_memoryPtr(memory)
    , m_memory(*memory)
    , m_keyboardPtr(keyboard)
    , m_keyboard(*keyboard)
{}

void Chip8::CPU::CLS() const
{
    m_screenPtr->Refresh(true);
}

void Chip8::CPU::RET() const
{
    assert(m_memory.sp > 0);
    m_memory.pc = m_memory.stack[m_memory.sp];
    --m_memory.sp;
}

void Chip8::CPU::JP(const std::uint16_t nnn) const
{
    assert(nnn <= 0xFFF);
    m_memory.pc = nnn;
}

void Chip8::CPU::CALL(const std::uint16_t nnn) const
{
    assert(nnn <= 0xFFF);
    ++m_memory.sp;
    m_memory.stack[m_memory.sp] = m_memory.pc;
    m_memory.pc = nnn;
}

void Chip8::CPU::LD_XKK(const std::uint8_t x, const std::uint8_t kk) const
{
    m_memory.VX[x] = kk;
}

void Chip8::CPU::ADD_XKK(const std::uint8_t x, const std::uint8_t kk) const
{
    m_memory.VX[x] += kk;
}

void Chip8::CPU::LD_XY(const std::uint8_t x, const std::uint8_t y) const
{
    m_memory.VX[x] = m_memory.VX[y];
}

void Chip8::CPU::OR(const std::uint8_t x, const std::uint8_t y) const
{
    m_memory.VX[x] |= m_memory.VX[y];
}

void Chip8::CPU::AND_XY(const std::uint8_t x, const std::uint8_t y) const
{
    m_memory.VX[x] &= m_memory.VX[y];
}

void Chip8::CPU::XOR(const std::uint8_t x, const std::uint8_t y) const
{
    m_memory.VX[x] ^= m_memory.VX[y];
}

void Chip8::CPU::ADD_XY(const std::uint8_t x, const std::uint8_t y) const
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
}

void Chip8::CPU::SUB(const std::uint8_t x, const std::uint8_t y) const
{
    const std::int16_t sub = m_memory.VX[x] - m_memory.VX[y];
    m_memory.VX[0xF] = sub > 0 ? 1 : 0;
    m_memory.VX[x] = static_cast<uint8_t>(sub % 256); // TODO wtf? need to check how to handle this properly
}

void Chip8::CPU::SHR(const std::uint8_t x) const
{
    m_memory.VX[0xF] = m_memory.VX[x] & 0x000F;
    m_memory.VX[x] <<= 1;
}

void Chip8::CPU::SUBN(const std::uint8_t x, const std::uint8_t y) const
{
    const std::int16_t sub = m_memory.VX[y] - m_memory.VX[x];
    m_memory.VX[0xF] = (sub > 0) ? 1 : 0;
    m_memory.VX[x] = static_cast<uint8_t>(sub % 256); // TODO wtf? need to check how to handle this properly
}

void Chip8::CPU::SHL(const std::uint8_t x) const
{
    m_memory.VX[0xF] = m_memory.VX[x] & 0x000F;
    m_memory.VX[x] >>= 1;
}

void Chip8::CPU::LD_I(const std::uint16_t nnn) const
{
    assert(nnn <= 0xFFF);
    m_memory.I = nnn;
}

void Chip8::CPU::JP_V0(const std::uint16_t nnn) const
{
    assert(nnn <= 0xFFF);
    m_memory.pc = nnn + m_memory.VX[0];
}

void Chip8::CPU::RND(const std::uint8_t x, const std::uint8_t kk) const
{
    m_memory.VX[x] = m_random.Pick() & kk;
}

/* DRW Stuff */
std::vector<Chip8::Screen::Point> PointsToDraw(const std::vector<uint8_t>& sprite, const Chip8::Screen::Point point, const uint8_t width)
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
                toDraw.emplace_back( x + point.first, y + point.second );
            }
        }
    }

    assert(!toDraw.empty());
    return toDraw;
}
/* End of DRW Stuff */

void Chip8::CPU::DRW(const std::uint8_t ls4b, const std::uint8_t x, const std::uint8_t y) const
{
    assert(ls4b <= 0xF);
    std::vector<uint8_t> sprite(static_cast<std::size_t>(ls4b));
    for (std::size_t i = 0; i <= ls4b; ++i)
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
        collides |= m_screenPtr->Collides(x2, y2);
        wrappedPoints.emplace_back( x2, y2 );
    }
    m_memory.VX[0xF] = collides ? 1 : 0;
    m_screenPtr->DrawSprite(wrappedPoints);
    m_screenPtr->Refresh(false);
}

// TODO Test it
void Chip8::CPU::SKP(const std::uint8_t x)
{
    if (m_keyboard.m_state.hasPressedKey)
    {
        m_keyboard.m_state.hasPressedKey = false;
        if (static_cast<int>(m_keyboard.m_state.keyPressed) == static_cast<int>(x))
        {
            m_memory.pc += 2;
        }
    }
}

// TODO Test it
void Chip8::CPU::SKNP(const std::uint8_t x)
{
    if (m_keyboard.m_state.hasPressedKey)
    {
        m_keyboard.m_state.hasPressedKey = false;
    }
    else if (static_cast<int>(m_keyboard.m_state.keyPressed) != static_cast<int>(x))
    {
        m_memory.pc += 2;
    }
}

// Works as expected
void Chip8::CPU::LD_XK(std::uint8_t x)
{
    auto& kState = m_keyboard.m_state;
    kState.hasPressedKey = false;
    do
    {
        SDL_WaitEvent(&m_event);
        if (m_event.type == SDL_KEYDOWN)
        {
            const auto& keymap = m_keyboard.m_keymap;
            const auto elem = keymap.find(m_event.key.keysym.scancode);
            if (elem != keymap.end())
            {
                m_keyboard.m_state.hasPressedKey = true;
                m_keyboard.m_state.keyPressed = elem->second;
                break;
            }
        }
    } while (m_event.type != SDL_KEYDOWN);
    m_memory.VX[x] = static_cast<int>(kState.keyPressed);
}

void Chip8::CPU::LD_XD(const std::uint8_t x) const
{
    m_memory.VX[x] = m_memory.DT;
}

void Chip8::CPU::LD_DX(const std::uint8_t x) const
{
    m_memory.DT = m_memory.VX[x];
}

void Chip8::CPU::LD_SX(std::uint8_t x) const
{
    m_memory.ST = m_memory.VX[x];
}

void Chip8::CPU::ADD_IX(std::uint8_t x) const
{
    m_memory.I += m_memory.VX[x];
}

void Chip8::CPU::LD_FX(std::uint8_t x) const
{
    constexpr std::size_t char_size = 5;
    const std::uint16_t index = Memory::fontset_location + x * char_size;
    m_memory.I = index;
}

void Chip8::CPU::LD_BX(std::uint8_t x) const
{
    const std::uint8_t value = m_memory.VX[x];
    const std::size_t index = m_memory.I;

    m_memory.memory[index] = static_cast<std::uint8_t>(std::trunc(value / 100));
    m_memory.memory[index + 1] = static_cast<std::uint8_t>(std::trunc((value % 100) / 10));
    m_memory.memory[index + 2] = value % 10;
}

void Chip8::CPU::LD_IX(std::uint8_t x) const
{
    for (std::size_t i = 0; i <= x; ++i)
    {
        m_memory.memory[m_memory.I + i] = m_memory.VX[i];
    }
}

void Chip8::CPU::LD_XI(std::uint8_t x) const
{
    for (std::size_t i = 0; i <= x; ++i)
    {
        m_memory.VX[i] = m_memory.memory[m_memory.I + i];
    }
}

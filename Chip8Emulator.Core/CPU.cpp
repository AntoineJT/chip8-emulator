#include "include/CPU.hpp"

#include <cassert>
#include <random>

Chip8::CPU::CPU(Screen& screen, Memory& memory) noexcept
    : m_screen(screen)
    , m_memory(memory)
{}

void Chip8::CPU::CLS() const noexcept
{
    m_screen.Refresh(true);
}

void Chip8::CPU::RET() const noexcept
{
    assert(m_memory.sp > 0);
    m_memory.pc = m_memory.stack[m_memory.sp];
    --m_memory.sp;
}

void Chip8::CPU::JP(const std::uint16_t nnn) const noexcept
{
    assert(nnn <= 0xFFF);
    m_memory.pc = nnn;
}

void Chip8::CPU::CALL(const std::uint16_t nnn) const noexcept
{
    assert(nnn <= 0xFFF);
    ++m_memory.sp;
    m_memory.stack[m_memory.sp] = m_memory.pc;
    m_memory.pc = nnn;
}

void Chip8::CPU::LD_XKK(const std::uint8_t x, const std::uint8_t kk) const noexcept
{
    m_memory.VX[x] = kk;
}

void Chip8::CPU::ADD_XKK(const std::uint8_t x, const std::uint8_t kk) const noexcept
{
    m_memory.VX[x] += kk;
}

void Chip8::CPU::LD_XY(const std::uint8_t x, const std::uint8_t y) const noexcept
{
    m_memory.VX[x] = m_memory.VX[y];
}

void Chip8::CPU::OR(const std::uint8_t x, const std::uint8_t y) const noexcept
{
    m_memory.VX[x] |= m_memory.VX[y];
}

void Chip8::CPU::AND_XY(const std::uint8_t x, const std::uint8_t y) const noexcept
{
    m_memory.VX[x] &= m_memory.VX[y];
}

void Chip8::CPU::XOR(const std::uint8_t x, const std::uint8_t y) const noexcept
{
    m_memory.VX[x] ^= m_memory.VX[y];
}

void Chip8::CPU::ADD_XY(const std::uint8_t x, const std::uint8_t y) const noexcept
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

void Chip8::CPU::SUB(const std::uint8_t x, const std::uint8_t y) const noexcept
{
    const std::int16_t sub = m_memory.VX[x] - m_memory.VX[y];
    m_memory.VX[0xF] = sub > 0 ? 1 : 0;
    m_memory.VX[x] = static_cast<uint8_t>(sub % 256); // TODO wtf? need to check how to handle this properly
}

void Chip8::CPU::SHR(const std::uint8_t x) const noexcept
{
    m_memory.VX[0xF] = m_memory.VX[x] & 0x000F;
    m_memory.VX[x] <<= 1;
}

void Chip8::CPU::SUBN(const std::uint8_t x, const std::uint8_t y) const noexcept
{
    const std::int16_t sub = m_memory.VX[y] - m_memory.VX[x];
    m_memory.VX[0xF] = (sub > 0) ? 1 : 0;
    m_memory.VX[x] = static_cast<uint8_t>(sub % 256); // TODO wtf? need to check how to handle this properly
}

void Chip8::CPU::SHL(const std::uint8_t x) const noexcept
{
    m_memory.VX[0xF] = m_memory.VX[x] & 0x000F;
    m_memory.VX[x] >>= 1;
}

void Chip8::CPU::LD_I(const std::uint16_t nnn) const noexcept
{
    assert(nnn <= 0xFFF);
    m_memory.I = nnn;
}

void Chip8::CPU::JP_V0(const std::uint16_t nnn) const noexcept
{
    assert(nnn <= 0xFFF);
    m_memory.pc = nnn + m_memory.VX[0];
}

void Chip8::CPU::RND(const std::uint8_t x, const std::uint8_t kk) const noexcept
{
    // TODO Use only one rd and dist
    // instead of creating once each time
    // i.e in a class called Random

    // NOTE if those are const, then it doesn't compile
    // with gcc on linux
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 255);

    m_memory.VX[x] = dist(rd) & kk;
}

void Chip8::CPU::LD_XD(const std::uint8_t x) const noexcept
{
    m_memory.VX[x] = m_memory.DT;
}

void Chip8::CPU::LD_DX(const std::uint8_t x) const noexcept
{
    m_memory.DT = m_memory.VX[x];
}

void Chip8::CPU::LD_SX(std::uint8_t x) const noexcept
{
    m_memory.ST = m_memory.VX[x];
}

void Chip8::CPU::ADD_IX(std::uint8_t x) const noexcept
{
    m_memory.I += m_memory.VX[x];
}

void Chip8::CPU::LD_FX(std::uint8_t x) const noexcept
{
    constexpr std::size_t char_size = 5;
    const std::uint16_t index = Memory::fontset_location + x * char_size;
    m_memory.I = index;
}

void Chip8::CPU::LD_BX(std::uint8_t x) const noexcept
{
    const std::uint8_t value = m_memory.VX[x];
    const std::size_t index = m_memory.I;

    m_memory.memory[index] = static_cast<std::uint8_t>(std::trunc(value / 100));
    m_memory.memory[index + 1] = static_cast<std::uint8_t>(std::trunc((value % 100) / 10));
    m_memory.memory[index + 2] = value % 10;
}

void Chip8::CPU::LD_IX(std::uint8_t x) const noexcept
{
    for (std::size_t i = 0; i <= x; ++i)
    {
        m_memory.memory[m_memory.I + i] = m_memory.VX[i];
    }
}

void Chip8::CPU::LD_XI(std::uint8_t x) const noexcept
{
    for (std::size_t i = 0; i <= x; ++i)
    {
        m_memory.VX[i] = m_memory.memory[m_memory.I + i];
    }
}

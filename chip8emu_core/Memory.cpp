#include "include/Memory.hpp"

#include <vector>

#include "OpcodeValueFunc.hpp"

// TODO Support ETI 660
// See here: http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#2.1
// Begins at 0x200, because generally
// from 0x000 to 0x1FF, the memory was
// reserved for the interpreter
constexpr std::size_t entry_point = 0x200; // 512

// from http://devernay.free.fr/hacks/chip8/C8TECH10.HTM
static constexpr std::array<std::uint8_t, 80> font_set =
{
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80 // F
};

Chip8::Memory::Memory()
    : memory({0})
    , pc(entry_point)
    , sp(0)
    , VX({0})
    , I(0)
    , stack({0})
    , DT(0)
    , ST(0)
{
    // loads font set into memory
    LoadFontSet();
}

void Chip8::Memory::LoadFontSet()
{
    // TODO take a look at std::copy later
    constexpr size_t size = font_set.size();
    for (std::size_t i = 0; i < size; ++i)
    {
        memory[i] = font_set[i];
    }
}

void Chip8::Memory::LoadProgram(std::vector<char> data)
{
    std::size_t index = pc;
    for (const char& c : data)
    {
        memory[index] = c;
        ++index;
    }
}

std::uint16_t Chip8::Memory::NextInstruction() const noexcept
{
    const auto index = static_cast<std::size_t>(pc);
    return Utils::OpcodeValue(memory[index], memory[index + 1]);
}

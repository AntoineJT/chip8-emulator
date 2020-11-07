#include "Memory.hpp"

// TODO Support ETI 660
// See here: http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#2.1
// Begins at 0x200, because generally
// from 0x000 to 0x1FF, the memory was
// reserved for the interpreter
constexpr std::size_t entry_point = 0x200; // 512

Chip8::Memory::Memory()
    : m_memory({})
    , m_cursor(entry_point)
{}

void Chip8::Memory::Flush() noexcept
{
    m_memory.fill(0);
}

Chip8::Memory::MemoryData& Chip8::Memory::Data()
{
    return m_memory;
}

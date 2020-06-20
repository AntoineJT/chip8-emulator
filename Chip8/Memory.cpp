#include "Memory.hpp"

namespace Chip8
{
    Memory::Memory()
    = default;

    void Memory::Flush() noexcept
    {
        m_memory.fill(0);
    }

    Memory::MemoryData& Memory::Data()
    {
        return m_memory;
    }
}

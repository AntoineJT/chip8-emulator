#pragma once
#include <array>
#include <cstddef>
#include "utils/byte.hpp"

namespace Chip8
{
    class Memory
    {
        static constexpr std::size_t ram_size = 4096;

    public:
        using MemoryData = std::array<byte_t, ram_size>;

        Memory();
        void Flush() noexcept;
        MemoryData& Data();
    
    private:
        MemoryData m_memory;
        std::size_t m_cursor; // program counter
    };
}

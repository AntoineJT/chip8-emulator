#pragma once
#include <array>
#include <cstddef>
#include "utils/byte.hpp"

namespace Chip8
{
    // TODO Support ETI 660
    // See here: http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#2.1
    constexpr std::size_t entry_point_address = 0x200; // 512
    constexpr std::size_t ram_size = 4096 - entry_point_address;

    class Memory
    {
    public:
        using MemoryData = std::array<byte_t, ram_size>;
        Memory();
        void Flush() noexcept;
        MemoryData& Data();
    
    private:
        MemoryData m_memory = {};
    };
}

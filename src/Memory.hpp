#pragma once
#include <array>

namespace Chip8
{
    // constexpr std::size_t interpreter_reserved_ram = 0x200;
    // constexpr std::size_t ram_size = 4096 - interpreter_reserved_ram;
    // constexpr std::size_t eti660_offset = 0x600 - interpreter_reserved_ram;

    class Memory
    {
        // TODO Use std::byte when MSVC will support it or break compatibility with it
        using Byte = unsigned char;

    public:
        using MemoryData = std::array<Byte, 4096>;
        Memory();
        void Flush() noexcept;
        MemoryData& Data();
    private:
        MemoryData m_memory{};
    };
}

#pragma once
#include <array>
#include <cstddef>

namespace Chip8
{
    constexpr std::size_t interpreter_reserved_ram = 512;
    constexpr std::size_t ram_size = 4096 - interpreter_reserved_ram;

    class Memory
    {
        // TODO Use std::byte when MSVC will support it or break compatibility with it
        using byte = unsigned char;

    public:
        using MemoryData = std::array<byte, ram_size>;
        Memory();
        void Flush() noexcept;
        MemoryData& Data();
    private:
        MemoryData m_memory{};
    };
}

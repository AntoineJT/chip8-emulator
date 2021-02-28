#pragma once
#include <string>

#include "Memory.hpp"

namespace Chip8::Dump
{
    std::string DumpMemoryWithoutHeap(const Memory& mem);
    std::string DumpMemory(const Memory& mem);
    void DumpHeap(std::ostringstream& stream, const Chip8::Memory& mem);
    std::string DumpHeap(const Chip8::Memory& mem);
}

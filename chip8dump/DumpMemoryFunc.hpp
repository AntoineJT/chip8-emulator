#pragma once
#include <string>

#include "Memory.hpp"

namespace Chip8::Dump
{
    std::string DumpMemory(const Memory& mem);
    std::string DumpMemoryV2(const Chip8::Memory& mem, std::string& prevHeapDump, std::string& heapDump);
    void DumpHeap(std::ostringstream& stream, const Chip8::Memory& mem);
    std::string DumpHeap(const Chip8::Memory& mem);
}

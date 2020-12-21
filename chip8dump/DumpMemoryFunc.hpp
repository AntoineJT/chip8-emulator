#pragma once
#include <string>

#include "Memory.hpp"

namespace Chip8::Dump
{
    std::string DumpMemory(const Memory& mem) noexcept;
}

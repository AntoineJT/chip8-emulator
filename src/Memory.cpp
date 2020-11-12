#include "Memory.hpp"

// TODO Support ETI 660
// See here: http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#2.1
// Begins at 0x200, because generally
// from 0x000 to 0x1FF, the memory was
// reserved for the interpreter
constexpr std::size_t entry_point = 0x200; // 512

Chip8::Memory::Memory()
    : memory({0})
    , pc(entry_point)
    , sp(0)
    , VX({0})
    , I(0)
    , stack({0})
    , DT(0)
    , ST(0)
{}

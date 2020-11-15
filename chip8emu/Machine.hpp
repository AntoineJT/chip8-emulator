#pragma once
#include <cstdint>

#include "Memory.hpp"
#include "Screen.hpp"

namespace Chip8
{
    class Memory;

    class Machine
    {
        Screen& m_screen;
        Memory& m_memory;

    public:
        Machine(Screen& screen, Memory& memory);

        void ExecuteNextInstruction();
        void Execute(std::uint16_t opcode);
    };
}

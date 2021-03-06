#pragma once
#include <cstdint>

#include "CPU.hpp"
#include "Memory.hpp"
#include "Screen.hpp"

namespace Chip8
{
    class Machine
    {
        Screen& m_screen;
        Memory& m_memory;
        CPU m_cpu;
        // avoids to allocate/destroy this struct
        // a lot of time per second
        SDL_Event m_event;

    public:
        Machine(Screen& screen, Memory& memory) noexcept;

        void ExecuteNextInstruction() const noexcept;
        void Execute(std::uint16_t opcode) const noexcept;
        void HandleEvents() noexcept;
    };
}

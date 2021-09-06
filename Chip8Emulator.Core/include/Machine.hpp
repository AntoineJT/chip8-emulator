#pragma once
#include <cstdint>

#include "CPU.hpp"
#include "Keyboard.hpp"
#include "Memory.hpp"
#include "Screen.hpp"

namespace Chip8
{
    class Machine
    {
        std::shared_ptr<Memory> m_memoryPtr;
        std::shared_ptr<Keyboard> m_keyboardPtr;
        CPU m_cpu;
        // avoids to allocate/destroy this struct
        // a lot of time per second
        SDL_Event m_event {};

    public:
        Machine(std::shared_ptr<Screen> screen, std::shared_ptr<Memory> memory, std::shared_ptr<Keyboard> keyboard);

        void ExecuteNextInstruction();
        void Execute(std::uint16_t opcode);
        void HandleEvents();
    };
}

#pragma once
#include <cstdint>
#include <thread>

#include "CPU.hpp"
#include "Keyboard.hpp"
#include "Memory.hpp"
#include "Screen.hpp"

#include "../vendor/timercpp/timercpp.hpp"

namespace Chip8
{
    class Machine
    {
        std::unique_ptr<Memory> m_memoryPtr;
        std::unique_ptr<Keyboard> m_keyboardPtr;
        CPU m_cpu;
        // avoids to allocate/destroy this struct
        // a lot of time per second
        SDL_Event m_event {};
        Timer m_soundTimer;
        Timer m_delayTimer;

        void InitTimers();

    public:
        Machine(std::shared_ptr<Screen> screen, std::unique_ptr<Memory> memory, std::unique_ptr<Keyboard> keyboard = std::make_unique<Keyboard>());
        Machine(std::shared_ptr<Screen> screen, const std::string& filepath);

        void ExecuteNextInstruction();
        void Execute(std::uint16_t opcode);
        void HandleEvents();

        Memory* GetMemory();
    };
}

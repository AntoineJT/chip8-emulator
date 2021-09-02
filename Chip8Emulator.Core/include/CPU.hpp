#pragma once

#include "Keyboard.hpp"
#include "Memory.hpp"
#include "Random.hpp"
#include "Screen.hpp"

namespace Chip8
{
    class CPU
    {
        std::shared_ptr<Screen> m_screenPtr;
        Screen& m_screen;

        std::shared_ptr<Memory> m_memoryPtr;
        Memory& m_memory;

        std::shared_ptr<Keyboard> m_keyboardPtr;
        Keyboard& m_keyboard;

        // avoids to allocate/destroy this struct
        // a lot of time per second
        SDL_Event m_event {};

        Random m_random = Random(0, 255);
        Key m_key = Key::NONE;

    public:
        CPU(std::shared_ptr<Screen> screen, std::shared_ptr<Memory> memory, std::shared_ptr<Keyboard> keyboard);

        void CLS() const;
        void RET() const;
        void JP(std::uint16_t nnn) const;
        void CALL(std::uint16_t nnn) const;
        void LD_XKK(std::uint8_t x, std::uint8_t kk) const;
        void ADD_XKK(std::uint8_t x, std::uint8_t kk) const;
        void LD_XY(std::uint8_t x, std::uint8_t y) const;
        void OR(std::uint8_t x, std::uint8_t y) const;
        void AND_XY(std::uint8_t x, std::uint8_t y) const;
        void XOR(std::uint8_t x, std::uint8_t y) const;
        void ADD_XY(std::uint8_t x, std::uint8_t y) const;
        void SUB(std::uint8_t x, std::uint8_t y) const;
        void SHR(std::uint8_t x) const;
        void SUBN(std::uint8_t x, std::uint8_t y) const;
        void SHL(std::uint8_t x) const;
        void LD_I(std::uint16_t nnn) const;
        void JP_V0(std::uint16_t nnn) const;
        void RND(std::uint8_t x, std::uint8_t kk) const;
        void DRW(std::uint8_t ls4b, std::uint8_t x, std::uint8_t y) const;
        void SKP(std::uint8_t x);
        void LD_XD(std::uint8_t x) const;
        void LD_DX(std::uint8_t x) const;
        void LD_SX(std::uint8_t x) const;
        void ADD_IX(std::uint8_t x) const;
        void LD_FX(std::uint8_t x) const;
        void LD_BX(std::uint8_t x) const;
        void LD_IX(std::uint8_t x) const;
        void LD_XI(std::uint8_t x) const;
    };
}

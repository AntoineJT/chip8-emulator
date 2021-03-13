#pragma once

#include "Keyboard.hpp"
#include "Memory.hpp"
#include "Random.hpp"
#include "Screen.hpp"

namespace Chip8
{
    class CPU
    {
        Screen& m_screen;
        Memory& m_memory;
        Keyboard& m_keyboard;
        Random m_random = Random(0, 255);

    public:
        CPU(Screen& screen, Memory& memory, Keyboard& keyboard) noexcept;

        void CLS() const noexcept;
        void RET() const noexcept;
        void JP(std::uint16_t nnn) const noexcept;
        void CALL(std::uint16_t nnn) const noexcept;
        void LD_XKK(std::uint8_t x, std::uint8_t kk) const noexcept;
        void ADD_XKK(std::uint8_t x, std::uint8_t kk) const noexcept;
        void LD_XY(std::uint8_t x, std::uint8_t y) const noexcept;
        void OR(std::uint8_t x, std::uint8_t y) const noexcept;
        void AND_XY(std::uint8_t x, std::uint8_t y) const noexcept;
        void XOR(std::uint8_t x, std::uint8_t y) const noexcept;
        void ADD_XY(std::uint8_t x, std::uint8_t y) const noexcept;
        void SUB(std::uint8_t x, std::uint8_t y) const noexcept;
        void SHR(std::uint8_t x) const noexcept;
        void SUBN(std::uint8_t x, std::uint8_t y) const noexcept;
        void SHL(std::uint8_t x) const noexcept;
        void LD_I(std::uint16_t nnn) const noexcept;
        void JP_V0(std::uint16_t nnn) const noexcept;
        void RND(std::uint8_t x, std::uint8_t kk) const noexcept;
        void DRW(std::uint8_t ls4b, std::uint8_t x, std::uint8_t y) const noexcept;
        void LD_XD(std::uint8_t x) const noexcept;
        void LD_DX(std::uint8_t x) const noexcept;
        void LD_SX(std::uint8_t x) const noexcept;
        void ADD_IX(std::uint8_t x) const noexcept;
        void LD_FX(std::uint8_t x) const noexcept;
        void LD_BX(std::uint8_t x) const noexcept;
        void LD_IX(std::uint8_t x) const noexcept;
        void LD_XI(std::uint8_t x) const noexcept;
    };
}

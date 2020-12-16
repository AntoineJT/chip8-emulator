#pragma once

#include <cstdint>
#include <string>

namespace Chip8::Disasm
{
    std::string Opcode2Asm(std::uint16_t opcode);
}

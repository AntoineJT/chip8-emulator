#pragma once

#include <string>
#include <cstdint>

namespace Chip8::Disasm
{
    std::string Opcode2Asm(std::uint16_t opcode);
}

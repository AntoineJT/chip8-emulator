#pragma once

#include <string>

namespace Chip8::Disasm
{
    // Write file, removes all its previous content
    void WriteTextFile(const std::string& filename, const std::string& textContent);
}

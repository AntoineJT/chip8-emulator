#pragma once
#include <string>
#include <vector>

namespace Chip8::Utils
{
    std::vector<char> LoadFile(const std::string& filename);
    bool LoadFile(std::vector<char>& content, const std::string& filename) noexcept;
}

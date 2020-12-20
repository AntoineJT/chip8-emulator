#include "include/LoadFileFunc.hpp"

#include <cstring>
#include <fstream>
#include <stdexcept>

std::vector<char> Chip8::Utils::LoadFile(const std::string& filename) noexcept
{
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open '" + filename + "'.");
    }

    const auto end = file.tellg();
    file.seekg(0, std::ios::beg);
    const auto size = std::size_t(end - file.tellg());

    if (size == 0) {
        throw std::runtime_error("The file '" + filename + "' was empty.");
    }

    std::vector<char> content(size);
    if (!file.read(content.data(), content.size())) {
        throw std::runtime_error(filename + ": " + std::strerror(errno));
    }
    file.close();

    return content;
}

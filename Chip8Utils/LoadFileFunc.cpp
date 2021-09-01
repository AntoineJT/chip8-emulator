#include "LoadFileFunc.hpp"

#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>

std::vector<char> Chip8::Utils::LoadFile(const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open '" + filename + "'. Does it exist?");
    }

    const auto end = file.tellg();
    file.seekg(0, std::ios::beg);
    const auto size = static_cast<std::size_t>(end - file.tellg());

    if (size == 0)
    {
        throw std::runtime_error("The file '" + filename + "' was empty.");
    }

    std::vector<char> content(size);
    if (!file.read(content.data(), content.size()))
    {
        throw std::runtime_error(filename + ": " + std::strerror(errno));
    }
    file.close();

    return content;
}

bool Chip8::Utils::LoadFile(std::vector<char>& content, const std::string& filename)
{
    try
    {
        content = LoadFile(filename);
    }
    catch (const std::runtime_error& err)
    {
        std::cerr << "Can't load '" << filename << "' content: " << err.what() << std::endl;
        return false;
    }
    return true;
}

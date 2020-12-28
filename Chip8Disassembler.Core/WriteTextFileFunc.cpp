#include "WriteTextFileFunc.hpp"

#include <fstream>

// Write file, removes all its previous content
void Chip8::Disasm::WriteTextFile(const std::string& filename, const std::string& textContent)
{
    std::fstream file;
    file.open(filename, std::ios::out | std::ios::trunc);
    if (!file.is_open())
    {
        throw std::runtime_error("Can't create file '" + filename + "'.");
    }
    file << textContent;
    file.close();
}

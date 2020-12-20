#include <cstdlib>
#include <fstream>
#include <iostream>

#include "LoadFileFunc.hpp"
#include "Opcode2AsmFunc.hpp"
#include "OpcodeValueFunc.hpp"
#include "PrintUsageFunc.hpp"

// Write file, removes all its previous content
void WriteTextFile(const std::string& filename, const std::string& textContent) noexcept
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

int main(int argc, char* argv[])
{
    std::string filename;

    if (argc == 1) {
        std::cerr << "Not enough arguments." << std::endl;
        Chip8::Utils::PrintUsage(argv[0]);
        return EXIT_FAILURE;
    }
    if (argc == 2) {
        filename = argv[1];
    }
    else {
        std::cerr << "Too much arguments." << std::endl;
        Chip8::Utils::PrintUsage(argv[0]);
        return EXIT_FAILURE;
    }

    const auto content = Chip8::Utils::LoadFile(filename);

    const std::size_t size = content.size();
    std::string output;
    for (std::size_t i = 0; i < size; i += 2)
    {
        const uint16_t opcode = Chip8::Utils::OpcodeValue(content[i], content[i + 1]);
        output.append(Chip8::Disasm::Opcode2Asm(opcode));
        output.push_back('\n');
    }

    WriteTextFile(filename + "_DIS.ASM", output);
}

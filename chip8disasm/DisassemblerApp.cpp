#include <iostream>
#include <cstdlib>
#include <fstream>

#include "../chip8utils/includes/LoadFileFunc.hpp"
#include "Opcode2AsmFunc.hpp"

void PrintUsage(std::string const& filename)
{
    std::cout << "Usage: " << filename << " [inputfile]" << std::endl;
}

uint16_t ParseOpcodeValue(uint8_t upper, uint8_t lower)
{
    return (upper << 8) | lower;
}

// Write file, removes all its previous content
void WriteTextFile(const std::string& filename, std::string textContent)
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
    std::cout << "THIS IS BROKEN FOR NOW" << std::endl
        << "At least addresses (nnn) are wrong" << std::endl;

    std::string filename;

    if (argc == 1) {
        std::cout << "Not enough arguments." << std::endl;
        PrintUsage(argv[0]);
        return EXIT_FAILURE;
    }
    if (argc == 2) {
        filename = argv[1];
    }
    else {
        std::cout << "Too much arguments." << std::endl;
        PrintUsage(argv[0]);
        return EXIT_FAILURE;
    }

    auto content = Chip8::Utils::LoadFile(filename);

    const std::size_t size = content.size();
    std::string output;
    for (std::size_t i = 0; i < size; i += 2)
    {
        const uint16_t opcode = ParseOpcodeValue(content[i], content[i + 1]);
        output.append(Chip8::Disasm::Opcode2Asm(opcode));
        output.push_back('\n');
    }

    WriteTextFile(filename + "_DIS.ASM", output);

    return EXIT_SUCCESS;
}

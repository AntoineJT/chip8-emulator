#include <cstdlib>
#include <iostream>

#include "LoadFileFunc.hpp"
#include "Opcode2AsmFunc.hpp"
#include "OpcodeValueFunc.hpp"
#include "PrintUsageFunc.hpp"
#include "WriteTextFileFunc.hpp"

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

    std::vector<char> content;
    try
    {
        content = Chip8::Utils::LoadFile(filename);
    }
    catch (const std::runtime_error& err)
    {
        std::cerr << "Can't load '" << filename << "' content: " << err.what() << std::endl;
        return EXIT_FAILURE;
    }

    const std::size_t size = content.size();
    std::string output;
    for (std::size_t i = 0; i < size; i += 2)
    {
        const uint16_t opcode = Chip8::Utils::OpcodeValue(content[i], content[i + 1]);
        output.append(Chip8::Disasm::Opcode2Asm(opcode));
        output.push_back('\n');
    }

    Chip8::Disasm::WriteTextFile(filename + "_DIS.ASM", output);
}

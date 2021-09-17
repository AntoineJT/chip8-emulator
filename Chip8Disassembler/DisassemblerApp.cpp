#include <cstdlib>
#include <iostream>

#include "LoadFileFunc.hpp"
#include "Opcode2AsmFunc.hpp"
#include "OpcodeValueFunc.hpp"
#include "PrintUsageFunc.hpp"
#include "WriteTextFileFunc.hpp"

int main(int argc, char* argv[])
{
    bool writeFile = false;

    switch (argc) {
    case 1:
        std::cerr << "Not enough arguments." << std::endl;
        Chip8::Utils::PrintUsage(argv[0]);
        return EXIT_FAILURE;
    case 2:
        // Nothing to do except
        // set filename value
        break;
    case 3:
        if (strcmp(argv[2], "--file") == 0) {
            writeFile = true;
        }
        break;
    default:
        std::cerr << "Too much arguments." << std::endl;
        Chip8::Utils::PrintUsage(argv[0]);
        return EXIT_FAILURE;
    }

    std::string filename = argv[1];
    std::vector<char> content;
    if (!Chip8::Utils::LoadFile(content, filename))
    {
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

    if (!writeFile) {
        std::cout << output << std::endl;
    }
    else {
        Chip8::Disasm::WriteTextFile(filename + "_DIS.ASM", output);
    }
}

#include "PrintUsageFunc.hpp"

#include <iostream>

void Chip8::Utils::PrintUsage(const char* filename)
{
    std::cerr << "Usage: " << filename << " <inputfile>" << std::endl;
}

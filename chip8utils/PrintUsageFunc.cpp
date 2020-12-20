#include "include/PrintUsageFunc.hpp"


#include <iostream>

void Chip8::Utils::PrintUsage(const char* filename)
{
    std::cout << "Usage: " << filename << " [inputfile]" << std::endl;
}

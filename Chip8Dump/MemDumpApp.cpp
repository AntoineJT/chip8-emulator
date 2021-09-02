#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>

#define SDL_MAIN_HANDLED

#include "CurrentDateFunc.hpp"
#include "DumpMemoryFunc.hpp"
#include "LoadFileFunc.hpp"
#include "Machine.hpp"
#include "Memory.hpp"
#include "Opcode2AsmFunc.hpp"
#include "Screen.hpp"
#include "sdl.hpp"

#include <SDL.h>
#include <tclap/CmdLine.h>

int main(int argc, char* argv[])
{
    TCLAP::CmdLine cmd("Chip8Emu Dump Tool");
    TCLAP::UnlabeledValueArg<std::string> filenameArg("inputfile", "Chip8 game file.", true, "", "string");
    TCLAP::ValueArg<int> delayArg("d", "delay", "Time in milliseconds between instructions. Default: 500.", false, 500, "time in ms");
    TCLAP::SwitchArg noHeapSwitch("n", "no-heap", "Don't dump heap memory.", false);
    cmd.add(filenameArg);
    cmd.add(delayArg);
    cmd.add(noHeapSwitch);
    cmd.parse(argc, argv);

    const std::string filename = filenameArg.getValue();
    int delay = delayArg.getValue();
    if (delay < 0)
    {
        delay = 0;
    }
    const bool noHeap = noHeapSwitch.getValue();

    const std::string ofname = filename + "_" + CurrentDate() + "_dump.txt";
    std::ofstream output(ofname);
    if (!output.is_open())
    {
        std::cerr << "Can't create file '" << ofname << "'!" << std::endl;
        return EXIT_FAILURE;
    }

    // sets up the emulator to be able to dump memory
    auto sdlPtr = std::make_shared<SDL2::SDL>(true);
    assert((*sdlPtr.get()).Init(SDL_INIT_VIDEO) == SDL2::SDL::INIT_SUCCESS);

    auto screenPtr = std::make_shared<Chip8::Screen>(sdlPtr, 4);
    sdlPtr.reset();

    std::vector<char> content;
    if (!Chip8::Utils::LoadFile(content, filename))
    {
        return EXIT_FAILURE;
    }
    auto memoryPtr = std::make_shared<Chip8::Memory>();
    auto& memory = *memoryPtr.get();
    memory.LoadProgram(content);

    auto keyboardPtr = std::make_shared<Chip8::Keyboard>();
    Chip8::Machine machine(screenPtr, memoryPtr, keyboardPtr);

    screenPtr.reset();
    keyboardPtr.reset();

    std::cout << "Press CTRL^C to quit" << std::endl;

    const auto& DumpMemoryFunc = noHeap ? Chip8::Dump::DumpMemoryWithoutHeap : Chip8::Dump::DumpMemory;
    while(true)
    {
        const std::uint16_t opcode = memory.NextInstruction();
        const std::string instruction = Chip8::Disasm::Opcode2Asm(opcode);

        machine.HandleEvents();
        machine.Execute(opcode);
        std::cout << instruction << std::endl;
        output << instruction << '\n'
            << DumpMemoryFunc(memory) << '\n';

        SDL_Delay(delay);
    }
}
    
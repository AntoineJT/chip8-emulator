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
    SDL2::SDL sdl(true);
    assert(sdl.Init(SDL_INIT_VIDEO) == SDL2::SDL::INIT_SUCCESS);
    Chip8::Screen screen(sdl, 4);
    Chip8::Memory mem;
    std::vector<char> content;
    if (!Chip8::Utils::LoadFile(content, filename))
    {
        return EXIT_FAILURE;
    }
    mem.LoadProgram(content);
    Chip8::Keyboard keyboard;
    Chip8::Machine machine(screen, mem, keyboard);

    std::cout << "Press CTRL^C to quit" << std::endl;

    const auto& DumpMemoryFunc = noHeap ? Chip8::Dump::DumpMemoryWithoutHeap : Chip8::Dump::DumpMemory;
    while(true)
    {
        const std::uint16_t opcode = mem.NextInstruction();
        const std::string instruction = Chip8::Disasm::Opcode2Asm(opcode);

        machine.HandleEvents();
        machine.Execute(opcode);
        std::cout << instruction << std::endl;
        output << instruction << '\n'
            << DumpMemoryFunc(mem) << '\n';

        SDL_Delay(delay);
    }
}
    
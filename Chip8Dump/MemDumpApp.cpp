#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <optional>

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

static std::string ExecNextInstruction(const Chip8::Memory& memory, Chip8::Machine& machine)
{
    const std::uint16_t opcode = memory.NextInstruction();
    machine.HandleEvents();
    machine.Execute(opcode);

    // return disassembled instruction
    return Chip8::Disasm::Opcode2Asm(opcode);
}

static inline int FloorAtZero(int val)
{
    if (val < 0)
        return 0;
    return val;
}

int main(int argc, char* argv[])
{
    TCLAP::CmdLine cmd("Chip8Emu Dump Tool");
    TCLAP::UnlabeledValueArg<std::string> filenameArg("inputfile", "Chip8 game file.", true, "", "string");
    TCLAP::ValueArg<int> delayArg("d", "delay", "Time between instructions. Default: 500.", false, 500, "time in ms");
    TCLAP::SwitchArg noHeapSwitch("n", "no-heap", "Don't dump heap memory.", false);
    TCLAP::SwitchArg noFileDumpSwitch("f", "no-file", "Only output basic infos on stdout.", false);
    TCLAP::ValueArg<int> windowRatioArg("r", "ratio", "Set window size. Default: 6", false, 6, "times the base resolution");
    cmd.add(filenameArg);
    cmd.add(delayArg);
    cmd.add(noHeapSwitch);
    cmd.add(noFileDumpSwitch);
    cmd.add(windowRatioArg);
    cmd.parse(argc, argv);

    const std::string filename = filenameArg.getValue();
    const int delay = FloorAtZero(delayArg.getValue());
    const bool noHeap = noHeapSwitch.getValue();
    const bool noFile = noFileDumpSwitch.getValue();
    const int ratio = FloorAtZero(windowRatioArg.getValue());

    std::optional<std::ofstream> output;
    if (!noFile) {
        const std::string ofname = filename + "_" + CurrentDate() + "_dump.txt";
        output = std::ofstream(ofname);
        if (!output->is_open())
        {
            std::cerr << "Can't create file '" << ofname << "'!" << std::endl;
            return EXIT_FAILURE;
        }
    }

    // sets up the emulator to be able to dump memory
    auto sdlPtr = std::make_shared<SDL2::SDL>(true);
    assert(sdlPtr->Init(SDL_INIT_VIDEO) == SDL2::SDL::INIT_SUCCESS);

    auto screenPtr = std::make_shared<Chip8::Screen>(sdlPtr, ratio, "Chip8Emu - Dump tool");
    sdlPtr.reset();

    std::vector<char> content;
    if (!Chip8::Utils::LoadFile(content, filename))
    {
        return EXIT_FAILURE;
    }
    auto memoryPtr = std::make_shared<Chip8::Memory>();
    auto& memory = *memoryPtr;
    memory.LoadProgram(content);

    Chip8::Machine machine(screenPtr, memoryPtr);
    screenPtr.reset();

    std::cout << "Press CTRL^C to quit" << std::endl;

    const auto DumpMemoryFunc = noHeap ? Chip8::Dump::DumpMemoryWithoutHeap : Chip8::Dump::DumpMemory;
    if (noFile) {
        while (true)
        {
            std::cout << ExecNextInstruction(memory, machine) << std::endl;
            SDL_Delay(delay);
        }
    }
    else {
        assert(output.has_value());
        while (true)
        {
            const std::string instruction = ExecNextInstruction(memory, machine);
            std::cout << instruction << std::endl;
            *output << instruction << '\n'
                << DumpMemoryFunc(memory) << '\n';
            SDL_Delay(delay);
        }
    }
}
    
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <thread>

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

static Chip8::Machine* sp_machine = nullptr;
static Chip8::Memory* sp_memory = nullptr;
static std::ofstream* sp_output = nullptr;
static bool s_noHeap = false;
static int s_delay = 0;

int EventThread(void* params)
{
    while (true)
    {
        sp_machine->HandleEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int MainThread(void* params)
{
    assert(sp_machine != nullptr && sp_memory != nullptr && sp_output != nullptr);

    const auto& DumpMemoryFunc = s_noHeap ? Chip8::Dump::DumpMemoryWithoutHeap : Chip8::Dump::DumpMemory;
    while (true)
    {
        const std::uint16_t opcode = sp_memory->NextInstruction();
        const std::string instruction = Chip8::Disasm::Opcode2Asm(opcode);

        sp_machine->Execute(opcode);
        std::cout << instruction << std::endl;
        *sp_output << instruction << '\n'
            << DumpMemoryFunc(static_cast<Chip8::Memory&>(*sp_memory)) << '\n';

        std::this_thread::sleep_for(std::chrono::milliseconds(s_delay));
    }
}

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
    const int delay = delayArg.getValue();
    if (delay > 0)
    {
        s_delay = delay;
    }
    s_noHeap = noHeapSwitch.getValue();

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
    Chip8::Machine machine(screen, mem);

    sp_machine = &machine;
    sp_memory = &mem;
    sp_output = &output;

    std::cout << "Press CTRL^C to quit" << std::endl;

    std::thread eventThread(EventThread, nullptr);
    std::thread mainThread(MainThread, nullptr);

    mainThread.join();
    eventThread.join();
}

#include "DumpMemoryFunc.hpp"

#include <cassert>
#include <cmath>
#include <string>
#include <sstream>

#include "Hex.hpp"
#include "Memory.hpp"

constexpr std::size_t turns = 64;

std::ostringstream DumpMemoryWithoutHeap(const Chip8::Memory& mem)
{
    std::ostringstream stream;

    // V0 - VF registers
    for (std::uint8_t i = 0x0; i <= 0xF; ++i)
    {
        stream << 'V' << Chip8::Hex::Uint4HexValue(i) << ": "
            << Chip8::Hex::U8ToHex(mem.VX[i]) << '\n';
    }

    // I register
    stream << "I: " << Chip8::Hex::U16ToHex(mem.I) << '\n';

    // stack pointer
    stream << "SP: " << Chip8::Hex::U8ToHex(mem.sp) << '\n';

    // stack content
    for (std::uint8_t i = 0x0; i <= 0xF; ++i)
    {
        stream << 'S' << Chip8::Hex::Uint4HexValue(i) << ": "
            << Chip8::Hex::U16ToHex(mem.stack[i]) << '\n';
    }

    // delay timer
    stream << "DT: " << Chip8::Hex::U8ToHex(mem.DT) << '\n';

    // sound timer
    stream << "ST: " << Chip8::Hex::U8ToHex(mem.ST) << '\n';

    // program counter
    stream << "PC: " << Chip8::Hex::U16ToHex(mem.pc) << '\n';

    return stream;
}

void Chip8::Dump::DumpHeap(std::ostringstream& stream, const Chip8::Memory& mem)
{
    static_assert(turns * turns == Memory::ram_size);
    for (std::size_t i = 0; i < turns; ++i)
    {
        for (std::size_t j = 0; j < turns; ++j)
        {
            stream << mem.memory[i * turns + j];
        }
        stream << '\n';
    }
}

std::string Chip8::Dump::DumpHeap(const Chip8::Memory& mem)
{
    std::ostringstream stream;
    DumpHeap(stream, mem);
    return stream.str();
}

std::string Chip8::Dump::DumpMemory(const Memory& mem)
{
    auto stream = DumpMemoryWithoutHeap(mem);
    stream << "Memory: " << '\n';
    DumpHeap(stream, mem);
    return stream.str();
}

// NOTE: I don't know if I need a vector or just one size_t + char
using diff_t = std::pair<std::size_t, char>;
using diffs = std::vector<diff_t>;

diffs CompareHeapDumps(std::string& prevHeapDump, std::string& heapDump)
{
    static_assert(turns * turns == Chip8::Memory::ram_size);

    constexpr std::size_t heap_size = Chip8::Memory::ram_size + turns; // this count the '\n' in the dumps
    assert(prevHeapDump.size() == heap_size);
    assert(heapDump.size() == heap_size);

    diffs result;

    for (std::size_t i = 0; i < turns; ++i)
    {
        for (std::size_t j = 0; j < turns; ++j)
        {
            const std::size_t index = i * turns + j;
            const char& prev = prevHeapDump[index];
            const char& cur = heapDump[index];

            if (prev != cur)
            {
                result.push_back({index, prev});
            }
        }
    }

    return result;
}

// TODO Fix it, avoid mutation on head dumps
std::string Chip8::Dump::DumpMemoryV2(const Memory& mem, std::string& prevHeapDump, std::string& heapDump)
{
    auto stream = DumpMemoryWithoutHeap(mem);
    stream << "Memory: " << '\n';
    if (prevHeapDump.empty())
    {
        stream << heapDump;
        return stream.str();
    }
    auto diff = CompareHeapDumps(prevHeapDump, heapDump);
    for (const diff_t& d : diff)
    {
        // TODO use trunc instead of floor
        stream << "@" << d.first - static_cast<std::size_t>(std::floor(d.first / turns)) << ": " << d.second << " -> " << heapDump[d.first];
    }
    return stream.str();
}

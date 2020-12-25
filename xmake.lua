set_project("chip8emu")
set_version("wip") -- will follow semver later

add_rules("mode.debug", "mode.release")
set_languages("cxx17")
set_symbols("debug", "edit")

add_requires("libsdl 2.0.12") -- latest version at the time

target("chip8emu")
    set_kind("binary")

    add_files("Chip8Emulator/*.cpp")
    add_headerfiles("Chip8Emulator/*.hpp")

    add_deps("Chip8Emulator.Core", "chip8utils", "sdl2wrapper")
    add_includedirs("Chip8Emulator.Core/include")
    add_includedirs("sdl2wrapper/include")
    add_includedirs("chip8utils/include")

    add_packages("libsdl")

target("sdl2wrapper")
    set_kind("static")

    add_files("sdl2wrapper/*.cpp")
    add_headerfiles("sdl2wrapper/include/*.hpp")

    add_packages("libsdl")

target("chip8disasm")
    set_kind("binary")

    add_files("Chip8Disassembler/*.cpp")
    add_headerfiles("Chip8Disassembler/*.hpp")

    add_deps("Chip8Disassembler.Core", "chip8utils")
    add_includedirs("Chip8Disassembler.Core/include")
    add_includedirs("chip8utils/include")

target("chip8utils")
    set_kind("static")

    add_files("chip8utils/*.cpp")
    add_headerfiles("chip8utils/include/*.hpp")

target("Chip8Emulator.Core")
    set_kind("static")

    add_files("Chip8Emulator.Core/*.cpp")
    add_headerfiles("Chip8Emulator.Core/include/*.hpp")

    add_deps("chip8utils", "sdl2wrapper")
    add_includedirs("sdl2wrapper/include")
    add_includedirs("chip8utils/include")

    add_packages("libsdl")

target("Chip8Disassembler.Core")
    set_kind("static")

    add_files("Chip8Disassembler.Core/*.cpp")
    add_headerfiles("Chip8Disassembler.Core/include/*.hpp")

    add_deps("chip8utils")
    add_includedirs("chip8utils/include")

target("chip8dump")
    set_kind("binary")

    add_files("chip8dump/*.cpp")
    add_headerfiles("chip8dump/*.hpp")

    add_deps("Chip8Emulator.Core", "Chip8Disassembler.Core", "chip8utils", "sdl2wrapper")
    add_includedirs("Chip8Emulator.Core/include")
    add_includedirs("sdl2wrapper/include")
    add_includedirs("Chip8Disassembler.Core/include")
    add_includedirs("chip8utils/include")

    add_packages("libsdl")

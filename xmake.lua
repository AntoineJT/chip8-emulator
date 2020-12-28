set_xmakever("2.3.9")

set_project("chip8emu")
set_version("wip") -- will follow semver later

add_rules("mode.debug", "mode.release")
set_languages("cxx17")
set_symbols("debug", "edit")

add_requires("libsdl 2.0.12") -- latest version at the time

if is_mode("release") then
    set_optimize("fastest")
end

target("chip8emu")
    set_kind("binary")
    -- set_group("Applications")

    add_files("Chip8Emulator/*.cpp")
    add_headerfiles("Chip8Emulator/*.hpp")

    add_deps("chip8emu.core", "chip8utils", "sdl2wrapper")
    add_includedirs("Chip8Emulator.Core/include")
    add_includedirs("sdl2wrapper/include")
    add_includedirs("chip8utils/include")

    add_packages("libsdl")

target("sdl2wrapper")
    set_kind("static")
    -- set_group("Static libs")

    add_files("sdl2wrapper/*.cpp")
    add_headerfiles("sdl2wrapper/include/*.hpp")

    add_packages("libsdl")

target("chip8disasm")
    set_kind("binary")
    -- set_group("Applications")

    add_files("Chip8Disassembler/*.cpp")
    add_headerfiles("Chip8Disassembler/*.hpp")

    add_deps("chip8disasm.core", "chip8utils")
    add_includedirs("Chip8Disassembler.Core/include")
    add_includedirs("chip8utils/include")

target("chip8utils")
    set_kind("static")
    -- set_group("Static libs")

    add_files("chip8utils/*.cpp")
    add_headerfiles("chip8utils/include/*.hpp")

target("chip8emu.core")
    set_kind("static")
    set_basename("Chip8Emulator.Core")
    -- set_group("Static libs")

    add_files("Chip8Emulator.Core/*.cpp")
    add_headerfiles("Chip8Emulator.Core/include/*.hpp")

    add_deps("chip8utils", "sdl2wrapper")
    add_includedirs("sdl2wrapper/include")
    add_includedirs("chip8utils/include")

    add_packages("libsdl")

target("chip8disasm.core")
    set_kind("static")
    set_basename("Chip8Disassembler.Core")
    -- set_group("Static libs")

    add_files("Chip8Disassembler.Core/*.cpp")
    add_headerfiles("Chip8Disassembler.Core/include/*.hpp")

    add_deps("chip8utils")
    add_includedirs("chip8utils/include")

target("chip8dump")
    set_kind("binary")
    -- set_group("Applications")

    add_files("chip8dump/*.cpp")
    add_headerfiles("chip8dump/*.hpp")

    add_deps("chip8emu.core", "chip8disasm.core", "chip8utils", "sdl2wrapper")
    add_includedirs("Chip8Emulator.Core/include")
    add_includedirs("sdl2wrapper/include")
    add_includedirs("Chip8Disassembler.Core/include")
    add_includedirs("chip8utils/include")

    add_packages("libsdl")

target_end()

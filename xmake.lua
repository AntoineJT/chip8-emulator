set_project("Chip8Emu")
set_version("wip") -- will follow semver later

add_rules("mode.debug", "mode.release")
set_languages("cxx17")
set_symbols("debug", "edit")

add_requires("libsdl 2.0.12") -- latest version at the time

target("chip8emu")
    set_kind("binary")

    add_files("chip8emu/*.cpp")
    add_headerfiles("chip8emu/*.hpp")

    add_deps("chip8emu_core", "chip8utils", "sdl2wrapper")
    add_includedirs("chip8emu_core/include")
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

    add_files("chip8disasm/*.cpp")
    add_headerfiles("chip8disasm/*.hpp")

    add_deps("chip8disasm_core", "chip8utils")
    add_includedirs("chip8disasm_core/include")
    add_includedirs("chip8utils/include")

target("chip8utils")
    set_kind("static")

    add_files("chip8utils/*.cpp")
    add_headerfiles("chip8utils/include/*.hpp")

target("chip8emu_core")
    set_kind("static")

    add_files("chip8emu_core/*.cpp")
    add_headerfiles("chip8emu_core/include/*.hpp")

    add_deps("chip8utils", "sdl2wrapper")
    add_includedirs("sdl2wrapper/include")
    add_includedirs("chip8utils/include")

    add_packages("libsdl")

target("chip8disasm_core")
    set_kind("static")

    add_files("chip8disasm_core/*.cpp")
    add_headerfiles("chip8disasm_core/include/*.hpp")

    add_deps("chip8utils")
    add_includedirs("chip8utils/include")

target("chip8dump")
    set_kind("binary")

    add_files("chip8dump/*.cpp")
    add_headerfiles("chip8dump/*.hpp")

    add_deps("chip8emu_core", "chip8disasm_core", "chip8utils", "sdl2wrapper")
    add_includedirs("chip8emu_core/include")
    add_includedirs("sdl2wrapper/include")
    add_includedirs("chip8disasm_core/include")
    add_includedirs("chip8utils/include")

    add_packages("libsdl")

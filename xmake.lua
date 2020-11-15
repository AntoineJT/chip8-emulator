add_rules("mode.debug", "mode.release")
add_requires("libsdl 2.0.12") -- latest version at the time

target("chip8emu")
    set_kind("binary")
    set_languages("cxx17")
    add_files("chip8emu/*.cpp")
    add_headerfiles("chip8emu/*.hpp")
    add_packages("libsdl")
    add_deps("sdl2wrapper")
    add_includedirs("sdl2wrapper/includes")
    add_deps("chip8utils")
    add_includedirs("chip8utils/includes")

target("sdl2wrapper")
    set_kind("static")
    set_languages("cxx17")
    add_files("sdl2wrapper/*.cpp")
    add_headerfiles("sdl2wrapper/includes/*.hpp")
    add_packages("libsdl")

target("chip8disasm")
    set_kind("binary")
    set_languages("cxx17")
    add_files("chip8disasm/*.cpp")
    add_headerfiles("chip8disasm/*.hpp")
    add_deps("chip8utils")
    add_includedirs("chip8utils/includes")

target("chip8utils")
-- Will be a shared lib when it'll be bigger
-- and I understand how to link it correctly
    set_kind("static")
    set_languages("cxx17")
    add_files("chip8utils/*.cpp")
    add_headerfiles("chip8utils/includes/*.hpp")

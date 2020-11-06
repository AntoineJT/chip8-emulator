add_rules("mode.debug", "mode.release")
add_requires("libsdl 2.0.*") -- 2.0.8 for now

target("chip8emu")
    set_kind("binary")
    set_languages("cxx17")
    add_files("src/*.cpp")
    add_packages("libsdl")
    add_deps("sdl2wrapper")
    add_includedirs("sdl2wrapper/includes") -- Seems to be a weird ugly way to do

target("sdl2wrapper")
    set_kind("static")
    set_languages("cxx17")
    add_files("sdl2wrapper/*.cpp")
    add_packages("libsdl")

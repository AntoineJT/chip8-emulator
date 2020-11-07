-- Add dev branch of the official repo, because my PR was merged on 
-- it, and is not deployed on the master branch for now
add_repositories("xmake-dev https://github.com/xmake-io/xmake-repo dev")

add_rules("mode.debug", "mode.release")
add_requires("libsdl 2.0.12") -- latest version at the time

target("chip8emu")
    set_kind("binary")
    set_languages("cxx17")
    add_files("src/*.cpp")
	add_headerfiles("src/*.hpp")
    add_packages("libsdl")
    add_deps("sdl2wrapper")
    add_includedirs("sdl2wrapper/includes") -- Seems to be a weird ugly way to do

target("sdl2wrapper")
    set_kind("static")
    set_languages("cxx17")
    add_files("sdl2wrapper/*.cpp")
    add_headerfiles("sdl2wrapper/includes/*.hpp")
    add_packages("libsdl")
    add_headerfiles("sdl2wrapper/*.hpp")

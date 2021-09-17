set_xmakever("2.5.6")

set_project("chip8emu")
set_version("0.0.0") -- will follow semver later

set_allowedplats("windows", "linux")
set_allowedarchs("windows|x64", "linux|x86_64")

add_rules("mode.debug", "mode.release")
set_languages("cxx17")
set_symbols("debug", "edit")

add_requires("libsdl 2.0.16", {configs = {use_sdlmain = false}}) -- latest version at the time
add_requires("tclap 1.4.0-rc1") -- latest version at the time

if is_mode("release") then
    set_optimize("fastest")
end

-----------
-- RULES --
-----------
local shared_pkgs = {libsdl = true}

rule("copy_dlls")
    after_build("windows", function (target)
        for _, pkg in pairs(target:pkgs()) do
            if shared_pkgs[pkg:name()] then
                local libs = pkg._INFO.libfiles
                for _, lib in pairs(libs) do
                    if lib:sub(#lib - 3) == '.dll' then
                        os.cp(lib, target:targetdir())
                    end
                end

                -- Avoid to copy twice the dlls
                shared_pkgs[pkg:name()] = false
            end
        end
    end)

-------------------
-- TARGETS: APPS --
-------------------
target("chip8emu")
    set_kind("binary")
    set_group("Applications")

    add_rules("copy_dlls")

    add_files("Chip8Emulator/**.cpp")
    add_headerfiles("Chip8Emulator/**.hpp")

    add_deps("chip8emu.core", "sdl2wrapper")
    add_packages("libsdl")

target("chip8disasm")
    set_kind("binary")
    set_group("Applications")

    add_rules("copy_dlls")

    add_files("Chip8Disassembler/**.cpp")
    add_headerfiles("Chip8Disassembler/**.hpp")

    add_deps("chip8disasm.core", "chip8utils")

target("chip8dump")
    set_kind("binary")
    set_group("Applications")

    add_rules("copy_dlls")

    add_files("chip8dump/**.cpp")
    add_headerfiles("chip8dump/**.hpp")

    add_deps("chip8emu.core", "chip8disasm.core", "chip8utils", "sdl2wrapper")
    add_packages("libsdl", "tclap")

----------------------------
-- TARGETS: INTERNAL LIBS --
----------------------------
target("sdl2wrapper")
    set_kind("static")
    set_group("Static libs")

    add_files("sdl2wrapper/**.cpp")
    add_headerfiles("sdl2wrapper/**.hpp")
    add_includedirs("sdl2wrapper/include/", {public = true})

    add_packages("libsdl")

target("chip8utils")
    set_kind("static")
    set_group("Static libs")

    add_files("Chip8Utils/**.cpp")
    add_headerfiles("Chip8Utils/**.hpp")
    add_includedirs("Chip8Utils/include/", {public = true})

target("chip8emu.core")
    set_kind("static")
    set_basename("Chip8Emulator.Core")
    set_group("Static libs")

    add_files("Chip8Emulator.Core/**.cpp")
    add_headerfiles("Chip8Emulator.Core/**.hpp", "Chip8Emulator.Core/**.h")
    add_includedirs("Chip8Emulator.Core/include/", {public = true})

    add_deps("chip8utils", "sdl2wrapper")
    add_packages("libsdl")

target("chip8disasm.core")
    set_kind("static")
    set_basename("Chip8Disassembler.Core")
    set_group("Static libs")

    add_files("Chip8Disassembler.Core/**.cpp")
    add_headerfiles("Chip8Disassembler.Core/**.hpp")
    add_includedirs("Chip8Disassembler.Core/include/", {public = true})

    add_deps("chip8utils")

target_end()

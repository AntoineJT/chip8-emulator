require("premake", ">=5.0.0-alpha15")

include "../ThirdParty/Bins/SDL2-2.0.12/module.lua"

workspace "Chip8 Emulator"
    configurations { "Debug", "Release" }

    location("projects")

    warnings "Extra"

    flags { "MultiProcessorCompile" }
    
    cppdialect "C++17"

    platforms { "Win32", "Win64" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    filter "platforms:Win32"
        system "Windows"
        architecture "x86"

    filter "platforms:Win64"
        system "Windows"
        architecture "x86_64"

    project "Chip8Emu"
        kind "ConsoleApp"
        language "C++"
    
        files {
            "../Code/src/**.cpp",
            "../Code/src/**.hpp"
        }

        premake.extensions.sdl2.include()

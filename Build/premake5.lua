require("premake", ">=5.0.0-alpha15")

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

    filter "architecture:*86"
        links {
            "../ThirdParty/SDL2/lib/x86/SDL2.dll"
        }

    filter "architecture:*64"
        links {
            "../ThirdParty/SDL2/lib/x64/SDL2.dll"
        }

    project "Chip8Emu"
        kind "ConsoleApp"
        language "C++"
    
        includedirs {
            "../ThirdParty/SDL2/include/"
        }

        files {
            "../Code/src/**.cpp",
            "../Code/src/**.hpp"
        }

        configuration "windows"
            postbuildcommands { 
                "copy ..\\ThirdParty\\SDL2\\lib\\SDL2.dll projects\\bin\\%{cfg.platform}\\%{cfg.buildcfg}\\" }

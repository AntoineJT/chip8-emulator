premake.extensions.sdl2 = {}

local function sdl2_include()
	includedirs {
		"../ThirdParty/Bins/SDL2-2.0.12/include/"
	}

	filter "platforms:Win32"
		libdirs {
			"../ThirdParty/Bins/SDL2-2.0.12/x86"
		}

	filter "platforms:Win64"
		libdirs {
			"../ThirdParty/Bins/SDL2-2.0.12/x64"
		}

	links {
		os.findlib("SDL2")
	}
end

premake.extensions.sdl2.include = sdl2_include

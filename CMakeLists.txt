cmake_minimum_required(VERSION 3.0)

project(Chip8emu)

if(WIN32)
	file(GLOB chip8_SRC
		"src/*.hpp"
		"src/*.cpp"
	)

	add_executable(chip8emu ${chip8_SRC})
else()
	message("Only Windows is supported for now")
endif()

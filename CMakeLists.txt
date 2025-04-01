cmake_minimum_required(VERSION 3.10)

set(CMAKE_GENERATOR
        "Unix Makefiles"
        CACHE STRING "generator"
)

project(Arcade
        VERSION 1.0.0
        DESCRIPTION "Arcade gaming platform"
        LANGUAGES CXX
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g3 -fsanitize=address,leak,undefined -fanalyzer")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -fsanitize=address,leak,undefined -fanalyzer")
endif()

include(FindPkgConfig)

add_subdirectory(lib/ANAL)
add_subdirectory(Arcade)
add_subdirectory(Games/Minesweeper)

#add_subdirectory(Renderers/debug)
add_subdirectory(Renderers/SFML)
add_subdirectory(Renderers/SDL)
add_subdirectory(Renderers/NCURSES)

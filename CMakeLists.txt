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

add_subdirectory(Arcade)

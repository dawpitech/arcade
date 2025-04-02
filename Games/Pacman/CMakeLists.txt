file(GLOB_RECURSE src "src/*.cpp")
add_library(game_pacman SHARED ${src})

target_link_libraries(game_pacman
        PRIVATE anal
)

set_target_properties(
        game_pacman
        PROPERTIES PREFIX "${CMAKE_SOURCE_DIR}/Games/"
)

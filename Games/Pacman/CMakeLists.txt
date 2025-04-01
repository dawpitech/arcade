file(GLOB_RECURSE src "src/*.cpp")
add_library(arcade_pacman SHARED ${src})

target_link_libraries(arcade_pacman PRIVATE anal)

set_target_properties(
        arcade_pacman
        PROPERTIES PREFIX "${CMAKE_SOURCE_DIR}/lib/"
)

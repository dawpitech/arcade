file(GLOB_RECURSE src "src/*.cpp")
add_library(arcade_minesweeper SHARED ${src})

target_link_libraries(arcade_minesweeper
        PRIVATE anal
)

set_target_properties(
        arcade_minesweeper
        PROPERTIES PREFIX "${CMAKE_SOURCE_DIR}/lib/"
)

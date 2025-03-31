file(GLOB_RECURSE src "src/*.cpp")
add_library(arcade_ncurses SHARED ${src})

find_package(Curses REQUIRED)

target_link_libraries(arcade_ncurses
        PRIVATE anal
        PRIVATE ${CURSES_LIBRARIES}
)

set_target_properties(
        arcade_ncurses
        PROPERTIES PREFIX "${CMAKE_SOURCE_DIR}/lib/"
)

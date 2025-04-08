file(GLOB_RECURSE src "src/*.cpp")
add_library(arcade_snake SHARED ${src})

target_link_libraries(arcade_snake
        PRIVATE anal
)

set_target_properties(
        arcade_snake
        PROPERTIES PREFIX "${CMAKE_SOURCE_DIR}/lib/"
)

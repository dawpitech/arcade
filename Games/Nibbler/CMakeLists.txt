file(GLOB_RECURSE src "src/*.cpp")
add_library(arcade_nibbler SHARED ${src})

target_link_libraries(arcade_nibbler
        PRIVATE anal
)

set_target_properties(
        arcade_nibbler
        PROPERTIES PREFIX "${CMAKE_SOURCE_DIR}/lib/"
)

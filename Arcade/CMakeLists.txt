file(GLOB_RECURSE src "src/*.cpp")
add_executable(arcade ${src})

target_link_libraries(arcade PRIVATE anal)

set_target_properties(
        arcade
        PROPERTIES PREFIX "${CMAKE_SOURCE_DIR}/"
)

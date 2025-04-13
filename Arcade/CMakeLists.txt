file(GLOB_RECURSE src "src/*.cpp")
add_executable(arcade ${src})

target_link_libraries(arcade PRIVATE anal)

target_compile_options(arcade PRIVATE "-fno-gnu-unique")

set_target_properties(
        arcade
        PROPERTIES PREFIX "${CMAKE_SOURCE_DIR}/"
)

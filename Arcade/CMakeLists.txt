file(GLOB_RECURSE src "src/*.cpp")
add_executable(arcade ${src})

add_subdirectory(../lib/ANAL ${CMAKE_BINARY_DIR}/ANAL)
target_link_libraries(arcade PRIVATE anal)

set_target_properties(
        arcade
        PROPERTIES PREFIX "${CMAKE_SOURCE_DIR}/"
)

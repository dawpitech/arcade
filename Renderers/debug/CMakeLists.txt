file(GLOB_RECURSE src "src/*.cpp")
add_library(arcade_term_debug SHARED ${src})

target_link_libraries(arcade_term_debug PRIVATE anal)

set_target_properties(
        arcade_term_debug
        PROPERTIES PREFIX "${CMAKE_SOURCE_DIR}/lib/"
)

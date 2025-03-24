file(GLOB_RECURSE src "src/*.cpp")
add_library(arcade_sfml SHARED ${src})

#find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
pkg_search_module(SFML REQUIRED sfml-all)

target_link_libraries(arcade_sfml
        PRIVATE anal
        PRIVATE sfml-graphics sfml-window sfml-system)

set_target_properties(
        arcade_sfml
        PROPERTIES PREFIX "${CMAKE_SOURCE_DIR}/lib/"
)

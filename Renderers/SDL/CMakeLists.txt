file(GLOB_RECURSE src "src/*.cpp")
add_library(arcade_sdl SHARED ${src})

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_TTF REQUIRED SDL2_ttf)
pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image)

target_link_libraries(arcade_sdl
        PRIVATE anal
        PRIVATE ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_IMAGE_LIBRARIES}
)

target_include_directories(arcade_sdl PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})

set_target_properties(
        arcade_sdl
        PROPERTIES PREFIX "${CMAKE_SOURCE_DIR}/lib/"
)

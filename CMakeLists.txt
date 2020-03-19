project(nethell)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/game.cpp
    src/texture.cpp
)

include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -g)
# Note: debug information currently enabled above with the -g flag

cmake_minimum_required(VERSION 3.10)
project(sdl_and_bgfx_test CXX)

if(WIN32)
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_FLAGS " ")
else()
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_FLAGS "-O3")
endif()



set(CMAKE_CXX_FLAGS "-O3 -isystem")

set(SDL_STATIC ON)

ADD_SUBDIRECTORY(lib/SDL)
ADD_SUBDIRECTORY(lib/bgfx)

INCLUDE_DIRECTORIES(lib/SDL/include)

add_executable(test_1 src/test_1.cpp)
target_link_libraries(test_1 PRIVATE SDL3::SDL3-static bgfx)
target_link_options(test_1 PRIVATE "-static-libstdc++")

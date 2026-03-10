cmake_minimum_required(VERSION 3.10)
project(sdl_and_bgfx_test CXX)
set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-O3)

set(SDL_STATIC ON)

set(BGFX_BUILD_TOOLS OFF CACHE BOOL "" FORCE)
set(BGFX_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BGFX_BUILD_TESTS OFF CACHE BOOL "" FORCE)

ADD_SUBDIRECTORY(lib/SDL)
ADD_SUBDIRECTORY(lib/bgfx)

INCLUDE_DIRECTORIES(lib/SDL/include)

add_executable(test_1 src/test_1.cpp)
target_link_libraries(test_1 PRIVATE SDL3::SDL3-static bgfx)

if(WIN32)
    target_link_options(test_1 PRIVATE "-static-libgcc" "-static-libstdc++")
else()
    target_link_options(test_1 PRIVATE "-static-libstdc++")
endif()

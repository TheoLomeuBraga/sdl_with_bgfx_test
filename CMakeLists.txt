cmake_minimum_required(VERSION 3.10)
project(sdl_and_bgfx_test CXX)

set(CMAKE_CXX_STANDARD 20)

if(WIN32)
    #set(CMAKE_CXX_STANDARD 20)
else()
    #set(CMAKE_CXX_STANDARD 17)

endif()

set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-O3)

set(SDL_STATIC ON)

ADD_SUBDIRECTORY(lib/SDL)
ADD_SUBDIRECTORY(lib/bgfx)

INCLUDE_DIRECTORIES(lib/SDL/include)

add_executable(test_1 src/test_1.cpp)
target_link_libraries(test_1 PRIVATE SDL3::SDL3-static bgfx)
target_link_options(test_1 PRIVATE "-static-libstdc++")

if(WIN32)
    message("Configuring for Windows")
    # Add Windows-specific source files or flags
elseif(APPLE)
    message("Configuring for macOS")
    # Add macOS-specific source files or flags
elseif(UNIX)
    message("Configuring for UNIX/Linux")
    # Add Linux-specific source files or flags
else()
    message("Unknown operating system")
endif()

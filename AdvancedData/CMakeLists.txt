cmake_minimum_required(VERSION 3.9)
project(AdvancedData)

set(CMAKE_CXX_STANDARD 11)

add_executable(AdvancedData main.cpp shader.hpp stb_image.h)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework OPENGL")

target_link_libraries(AdvancedData "/usr/local/lib/libglfw.dylib")

target_link_libraries(AdvancedData "/usr/local/lib/libGLEW.dylib")
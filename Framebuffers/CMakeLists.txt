cmake_minimum_required(VERSION 3.9)
project(Framebuffers)

set(CMAKE_CXX_STANDARD 11)

add_executable(Framebuffers main.cpp shader.cpp shader.hpp)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework OPENGL")

target_link_libraries(Framebuffers "/usr/local/lib/libglfw.dylib")

target_link_libraries(Framebuffers "/usr/local/lib/libGLEW.dylib")
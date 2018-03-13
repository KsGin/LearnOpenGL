cmake_minimum_required(VERSION 3.9)
project(Color)

set(CMAKE_CXX_STANDARD 11)

add_executable(Color main.cpp shader.cpp shader.hpp)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework OPENGL")

target_link_libraries(Color "/usr/local/lib/libglfw.dylib")

target_link_libraries(Color "/usr/local/lib/libGLEW.dylib")
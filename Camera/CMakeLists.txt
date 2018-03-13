cmake_minimum_required(VERSION 3.9)
project(Camera)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp shader.cpp shader.hpp texture.hpp texture.cpp)

add_executable(Camera ${SOURCE_FILES})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework OPENGL")

target_link_libraries(Camera "/usr/local/lib/libglfw.dylib")

target_link_libraries(Camera "/usr/local/lib/libGLEW.dylib")
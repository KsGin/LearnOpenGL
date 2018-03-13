cmake_minimum_required(VERSION 3.8)
project(AColoredCube)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp shader.cpp shader.h)
add_executable(AColoredCube ${SOURCE_FILES})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework OPENGL")

target_link_libraries(AColoredCube "/usr/local/lib/libglfw.dylib")

target_link_libraries(AColoredCube "/usr/local/lib/libGLEW.dylib")